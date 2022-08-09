// Force to a right sintax
"use strict"

// Use electron included via npm
const { app, BrowserWindow } = require("electron");

// For preload paths
const path = require("path");

// Create a new window with a default file
const createWindow = (preload, pathload) => {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        frame: true,
        // preload paths
        webPreferences: {
            preload: path.join(__dirname, preload)
        }
    });

    // win.loadURL('https://kuzaftys.com');
    win.loadFile(pathload);
};

// Create a new window with a default url
const createWindowUrl = (pathload) => {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        frame: false
    });

    // win.loadURL('https://kuzaftys.com');
    win.loadURL(pathload);
};

// Show the window when the app is ready
app.whenReady().then(() => {
    // Create the window
    createWindow('preload.js', 'index.html');

    // Make sure to create one in macOS
    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) createWindow('preload.js', 'index.html');
    });
});

// Make secure the end of the application when all windows are closed
app.on('window-all-closed', () => {
    if(process.platform !== 'darwin') app.quit();
});