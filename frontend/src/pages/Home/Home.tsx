import {Stack, ToggleButton, ToggleButtonGroup, Typography} from '@mui/material';
import React, {useEffect, useState} from "react";
import CheckIcon from '@mui/icons-material/Check';
import crossroadPath from '../../assets/crossroad.jpg'
import carPath from '../../assets/car.webp'

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
    cars: Car,
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
        console.log("Redraw is called");
        
        const crossroadImage = new Image();
        crossroadImage.src = crossroadPath;
        const carImage = new Image();
        carImage.src = carPath;
        const resp = (await (await fetch("http://localhost:1234/cars")).json()) as Response;
        ctx.clearRect(0, 0, 800, 600);
        ctx.drawImage(crossroadImage, 0, 0);
        ctx.drawImage(carImage, resp.cars.pos.x, resp.cars.pos.y, carImage.width / 10, carImage.height / 10);
        ctx.fillStyle = resp.left_up_light_color;
        ctx.beginPath();
        ctx.arc(0, 0, 20, 0, 2 * Math.PI);
        ctx.fill()
        ctx.fillStyle = resp.left_down_light_color;
        ctx.beginPath();
        ctx.arc(0, 300, 20, 0, 2 * Math.PI);
        ctx.fill()
        ctx.fillStyle = resp.right_down_light_color;
        ctx.beginPath();
        ctx.arc(600, 300, 20, 0, 2 * Math.PI);
        ctx.fill()
        ctx.fillStyle = resp.right_up_light_color;
        ctx.beginPath();
        ctx.arc(500, 0, 20, 0, 2 * Math.PI);
        ctx.fill()
        requestAnimationFrame(redraw);
    };
    const redraw = throttle(redrawRaw, 0);
    requestAnimationFrame(redraw);

    return (
        <>
            <canvas ref={ setCanvas } width={ 800 } height={ 600 } />
        </>
    );
};

export default Home;