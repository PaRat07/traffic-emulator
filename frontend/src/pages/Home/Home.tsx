import {Stack, ToggleButton, ToggleButtonGroup, Typography} from '@mui/material';
import React, {useEffect, useState} from "react";
import CheckIcon from '@mui/icons-material/Check';
import crossroadPath from '../../assets/BigCrossRoad.jpeg'
import carPath from '../../assets/Car.png'

const throttle = (fn: Function, wait: number = 300) => {
    let inThrottle: boolean,
        lastFn: ReturnType<typeof setTimeout>,
        lastTime: number;
    return function (this: any) {
        const context = this,
            args = arguments;
        if (!inThrottle) {
            fn.apply(context, args);
            lastTime = Date.now();
            inThrottle = true;
        } else {
            clearTimeout(lastFn);
            lastFn = setTimeout(() => {
                if (Date.now() - lastTime >= wait) {
                    fn.apply(context, args);
                    lastTime = Date.now();
                }
            }, Math.max(wait - (Date.now() - lastTime), 0));
        }
    };
};

interface Pos {
    x: number,
    y: number
}

interface Car {
    pos: Pos,
    direction: number,
}

interface Response {
    cars: Car[],
    left_up_light_color: "red" | "yellow" | "green",
    left_down_light_color: "red" | "yellow" | "green",
    right_up_light_color: "red" | "yellow" | "green",
    right_down_light_color: "red" | "yellow" | "green"
}

const Home = () => {
    const [canvas, setCanvas] = useState<HTMLCanvasElement>();

    const redrawRaw = async () => {
        if (canvas == null) return;
        const ctx = canvas.getContext("2d");
        if (ctx === null) return;
        const crossroadImage = new Image();
        crossroadImage.src = crossroadPath;
        const carImage = new Image();
        carImage.src = carPath;
        const resp = (await (await fetch("http://localhost:1234/cars")).json()) as Response;
        ctx.clearRect(0, 0, 1498, 723);
        ctx.drawImage(crossroadImage, 0, 0);
        resp.cars.map((car) => {
            ctx.drawImage(carImage, car.pos.x, car.pos.y, carImage.width / 4, carImage.height / 4);
        });
        ctx.strokeStyle = "black";
        ctx.fillStyle = resp.left_up_light_color;
        ctx.beginPath();
        ctx.arc(560, 220, 20, 0, 2 * Math.PI);
        ctx.fill();
        ctx.arc(560, 220, 20, 0, 2 * Math.PI);
        ctx.stroke();
        ctx.fillStyle = resp.left_down_light_color;
        ctx.beginPath();
        ctx.arc(960, 220, 20, 0, 2 * Math.PI);
        ctx.fill();
        ctx.arc(960, 220, 20, 0, 2 * Math.PI);
        ctx.stroke();
        ctx.fillStyle = resp.right_down_light_color;
        ctx.beginPath();
        ctx.arc(560, 520, 20, 0, 2 * Math.PI);
        ctx.fill()
        ctx.arc(560, 520, 20, 0, 2 * Math.PI);
        ctx.stroke()
        ctx.fillStyle = resp.right_up_light_color;
        ctx.beginPath();
        ctx.arc(960, 520, 20, 0, 2 * Math.PI);
        ctx.fill()
        ctx.arc(960, 520, 20, 0, 2 * Math.PI);
        ctx.stroke()
        requestAnimationFrame(redrawRaw);
    };
    // const redraw = throttle(redrawRaw, 0);
    requestAnimationFrame(redrawRaw);

    return (
        <>
            <canvas ref={ setCanvas } width={ 1498 } height={ 723 } />
        </>
    );
};

export default Home;