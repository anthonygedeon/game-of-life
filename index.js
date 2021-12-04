"use strict";
var scale = 20;
var WIDTH = 640;
var HEIGHT = 320;
var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
canvas.width = WIDTH;
canvas.height = HEIGHT;
ctx.strokeStyle = "#cacaca";
ctx.globalCompositeOperation = "destination-over";
var grid = [];
var createGrid = function () {
    for (var i = 0; i < HEIGHT / scale; i++) {
        grid[i] = [];
        for (var j = 0; j < WIDTH / scale; j++) {
            ctx.strokeRect(j * scale, i * scale, scale, scale);
            grid[i][j] = { x: j, y: i, isAlive: false };
        }
    }
};
createGrid();
canvas.addEventListener("click", function (e) {
    var rect = canvas.getBoundingClientRect();
    var x = Math.floor((e.clientX - rect.left) / scale);
    var y = Math.floor((e.clientY - rect.top) / scale);
    grid[y][x] = { x: x, y: y, isAlive: true };
    grid.forEach(function (row) {
        row.forEach(function (col) {
            if (col.isAlive) {
                console.log(grid);
                ctx.fillRect(col.x * scale, col.y * scale, scale, scale);
            }
        });
    });
});
window.addEventListener("load", function () {
    createGrid();
});
document.addEventListener("wheel", function (e) {
    ctx.clearRect(0, 0, WIDTH, HEIGHT);
    scale += e.deltaY * -0.02;
    scale = Math.min(Math.max(8, scale), 20);
    createGrid();
});
