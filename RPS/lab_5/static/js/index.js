async function main() {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");
    const canvas_width = 900;
    const canvas_height = 700;
    const radius = 6;
    const points = await getAllPoints();
    const pointScaler = 4;

    // Координаты начальной и конечной точек для построения линии
    let coords = [{
        "x": 0,
        "y": 0
    }, {
        "x": 0,
        "y": 0
    }]

    // Номер клика == индексу в coords
    let click = 0

    // Отрисовка всех точек на холсте
    for (let i = 0; i < points.data.length; i++) {
        let point = points.data[i];

        renderPoint(point["x"] * pointScaler, point["y"] * pointScaler, radius, canvas_width, canvas_height, ctx);
    }

    canvas.addEventListener("mousedown", function (e) {
        let pos = getCursorPosition(canvas, e);

        // Данные пикселя, на который кликнули
        let imageData = ctx.getImageData(pos[0], pos[1], 1, 1).data;

        // Если пиксель цветной, то сохраняем координату точки
        if (imageData[0] || imageData[1] || imageData[2]) {
            coords[click].x = pos[0];
            coords[click].y = pos[1];

            click++;

            // Отрисовка линни
            if (click == 2) {
                let xPow = Math.pow((coords[1].x - coords[0].x), 2);
                let yPow = Math.pow((coords[1].y - coords[0].y), 2);
                let lineLength = Math.round(Math.sqrt(xPow + yPow));

                drawLineWithText(ctx, coords[0], coords[1], lineLength);
                click = 0;
            }
        }
    })
};

async function getAllPoints() {
    let allPoint = await fetch("http://127.0.0.1:7777/points")
        .then((response) => {
            return response.json();
        });
    return allPoint;
}

function renderPoint(x, y, radius, canvas_width, canvas_height, ctx) {
    let posX = (canvas_width / 2) + x;
    let posY = (canvas_height / 2) + y;

    ctx.beginPath();
    ctx.fillStyle = "red";
    ctx.arc(posX, posY, radius, 0, 2 * Math.PI);
    ctx.fill();
}

function getCursorPosition(canvas, event) {
    const rect = canvas.getBoundingClientRect();
    const x = Math.abs(Math.round(event.clientX - rect.left));
    const y = Math.abs(Math.round(event.clientY - rect.top));

    return [x, y];
}

function drawLineWithText(ctx, pointStart, pointEnd, text) {
    let centerX = pointStart.x + (pointEnd.x - pointStart.x) / 2;
    let centerY = pointStart.y + (pointEnd.y - pointStart.y) / 2;
    let lineCenterCoords = [centerX, centerY];

    ctx.strokeStyle = "red";
    ctx.lineWidth = 3;

    ctx.beginPath();
    ctx.moveTo(pointStart.x, pointStart.y);
    ctx.lineTo(pointEnd.x, pointEnd.y);
    ctx.stroke();

    ctx.fillStyle = "black";
    ctx.font = "bold 16px sans-serif";
    ctx.fillText(text, lineCenterCoords[0], lineCenterCoords[1]);
}

main()