const canvas = document.getElementById("canvas") as HTMLCanvasElement;
const ctx = canvas.getContext("2d") as CanvasRenderingContext2D;

const cell = {
    width: 20,
    height: 20,
};

let scale = 20;

canvas.width = 640;
canvas.height = 320;

canvas.addEventListener("click", (e) => {
    const rect = canvas.getBoundingClientRect();
    const x = Math.floor((e.clientX - rect.left) / scale) * scale;
    const y = Math.floor((e.clientY - rect.top) / scale) * scale;
    ctx.fillRect(x, y, scale, scale);
    console.log(x, y);
});

ctx.strokeStyle = "#cacaca";
ctx.globalCompositeOperation = "destination-over";

document.addEventListener("wheel", (e) => { 
    ctx.clearRect(0, 0, 640, 320);

    for (let i = 0; i < canvas.width; i += scale) {
        for (let j = 0; j < canvas.height; j += scale) {
           ctx.strokeRect(i, j, scale, scale);
        }
    }

   scale += Math.floor((e.deltaY * -0.01) - 0.03);

   console.log((e.deltaY * -0.01) - 0.03);
});