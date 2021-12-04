let scale = 20;
interface Cell {
    x: number;
    y: number;
    isAlive: boolean;
}

const WIDTH = 640;
const HEIGHT = 320;

const canvas = document.getElementById("canvas") as HTMLCanvasElement;
const ctx = canvas.getContext("2d") as CanvasRenderingContext2D;

canvas.width = WIDTH;
canvas.height = HEIGHT;

ctx.strokeStyle = "#cacaca";
ctx.globalCompositeOperation = "destination-over";

const grid: Cell[][] = []

const createGrid = () => {
    for (let i = 0; i < HEIGHT / scale; i++) {
        grid[i] = [];
        for (let j = 0; j < WIDTH / scale; j++) {
            ctx.strokeRect(j*scale, i*scale, scale, scale);
            grid[i][j] = {x: j, y: i, isAlive: false};
        }
    }
}

createGrid();

canvas.addEventListener("click", (e) => {
    const rect = canvas.getBoundingClientRect();
    const x = Math.floor((e.clientX - rect.left) / scale);
    const y = Math.floor((e.clientY - rect.top) / scale);
    grid[y][x] = {x, y, isAlive: true};
    grid.forEach(row => {
       row.forEach(col => {
           if (col.isAlive) {
               console.log(grid);
               ctx.fillRect(col.x*scale, col.y*scale, scale, scale);
           }
       })
   }) 
});

window.addEventListener("load", () => {
    createGrid();
});

document.addEventListener("wheel", (e) => { 
    ctx.clearRect(0, 0, WIDTH, HEIGHT);
    scale += e.deltaY * -0.02;
    scale = Math.min(Math.max(8, scale), 20);
    createGrid();
});
