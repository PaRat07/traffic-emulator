import {Stack, ToggleButton, ToggleButtonGroup, Typography} from '@mui/material';
import React, {useEffect, useState} from "react";
import CheckIcon from '@mui/icons-material/Check';


const Home = () => {
    const [canvas, setCanvas] = useState<HTMLCanvasElement>();

    useEffect(() => {
        if (canvas == null) return;
        const ctx = canvas.getContext("2d");
        const landscape = new Image();
        landscape.src = "/crossroad.jpg";
        const car = new Image();
        car.src = "/car.webp";
        let pos = 0;
        const loop = () => {
            ctx.clearRect(0, 0, 800, 600);
            ctx.drawImage(landscape, 0, 0);
            ctx.drawImage(car, pos, pos, car.width / 10, car.height / 10);
            ctx.stroke()
            pos += 1;
            if (pos < 500) {
                requestAnimationFrame(loop)
            }
        }
        requestAnimationFrame(loop);
        return () => {};
    }, [canvas]);
    return (
        <>
            <canvas ref={ setCanvas } width={ 800 } height={ 600 }></canvas>
        </>
    );
};

export default Home;