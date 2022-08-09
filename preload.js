"use strict"

// Spawn functions
const { spawn } = require("child_process");

// Create an event
window.addEventListener('DOMContentLoaded', () => {
    // Replace text function
    // Send an ID selector and text to place in
    const replaceText = (selector, text) => {
        const element = document.getElementById(selector);
        // Place if element found
        if (element) element.innerText = text;
    }

    for (const dependency of ['chrome', 'node', 'electron']) {
        replaceText(`${dependency}-version`, process.versions[dependency]);
    }

    // Add function to greeting
    const greet = (listener, args) => {
        const ls = spawn(listener, args);
        ls.stdout.on('data', (data) => {
            console.log(`stdout: ${data}`);
        });
          
        ls.stderr.on('data', (data) => {
            console.error(`stderr: ${data}`);
        });
          
        ls.on('close', (code) => {
            console.log(`child process exited with code ${code}`);
        });
    }

    const buttonGreet = document.getElementById('greeting');
    if (buttonGreet) {
        buttonGreet.addEventListener("click", () => {
            greet('ls', ['-l', '/usr'])
        }, false);
    }

});