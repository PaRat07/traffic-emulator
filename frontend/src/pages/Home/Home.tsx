import {Stack, ToggleButton, ToggleButtonGroup, Typography} from '@mui/material';
import React, {useCallback, useEffect, useRef, useState} from "react";
import CheckIcon from '@mui/icons-material/Check';
import crossroadPath from '../../assets/BigCrossRoad.jpeg'
import carPath from '../../assets/Car.png'


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
    let resp = useRef<Response | null>(null);
    const [flag, setFlag] = useState<number>(0);
    const handleNewData = useCallback((resp_json: MessageEvent) => {
        resp.current = JSON.parse(resp_json.data);
        setFlag((prevValue) => {
            return prevValue + 1;
    });
    }, [flag]);
    useEffect(() => {
        (new WebSocket("ws://localhost:1234/cars")).onmessage = handleNewData
    }, []);


    const [canvas, setCanvas] = useState<HTMLCanvasElement>();

    useEffect(() => {
        if (canvas == null) return;
        const ctx = canvas.getContext("2d");
        if (ctx === null) return;
        const crossroadImage = new Image();
        crossroadImage.src = crossroadPath;
        const carImage = new Image();
        carImage.src = carPath;
        console.log(resp.current.left_down_light_color);
        if (resp.current === null || resp.current.cars === undefined) return;
        ctx.clearRect(0, 0, 1498, 723);
        ctx.drawImage(crossroadImage, 0, 0);
        resp.current.cars.map((car) => {
            const radians = car.direction * Math.PI / 180;
            ctx.translate(car.pos.x, car.pos.y);
            ctx.rotate(radians);
            ctx.drawImage(carImage, -carImage.width / 8, -carImage.height / 8, carImage.width / 4, carImage.height / 4);
            ctx.setTransform(1, 0, 0, 1, 0, 0);
        });
        ctx.strokeStyle = "black";
        ctx.fillStyle = resp.current.left_up_light_color;
        ctx.beginPath();
        ctx.arc(560, 220, 20, 0, 2 * Math.PI);
        ctx.fill();
        ctx.arc(560, 220, 20, 0, 2 * Math.PI);
        ctx.stroke();
        ctx.fillStyle = resp.current.left_down_light_color;
        ctx.beginPath();
        ctx.arc(560, 520, 20, 0, 2 * Math.PI);
        ctx.fill();
        ctx.arc(560, 520, 20, 0, 2 * Math.PI);
        ctx.stroke();
        ctx.fillStyle = resp.current.right_down_light_color;
        ctx.beginPath();
        ctx.arc(960, 520, 20, 0, 2 * Math.PI);
        ctx.fill()
        ctx.arc(960, 520, 20, 0, 2 * Math.PI);
        ctx.stroke()
        ctx.fillStyle = resp.current.right_up_light_color;
        ctx.beginPath();
        ctx.arc(960, 220, 20, 0, 2 * Math.PI);
        ctx.fill()
        ctx.arc(960, 220, 20, 0, 2 * Math.PI);
        ctx.stroke()
    }, [flag]);

    return (
        <>
            <canvas ref={ setCanvas } width={ 1498 } height={ 723 } />
        </>
    );
};

export default Home;