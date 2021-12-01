const canvas = document.getElementById("canvas") as HTMLCanvasElement;
const ctx = canvas.getContext("2d") as CanvasRenderingContext2D;

canvas.width = 640;
canvas.height = 320;

ctx.fillStyle = "green";
ctx.fillRect(0, 0, 10, 10);

