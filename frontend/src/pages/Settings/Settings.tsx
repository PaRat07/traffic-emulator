import {
    Box, Button,
    ButtonGroup,
    FormControlLabel,
    Stack,
    Switch,
    ToggleButton,
    ToggleButtonGroup,
    Typography
} from '@mui/material';
import Grid from '@mui/material/Unstable_Grid2/Grid2';
import React, {useContext, useState} from 'react';
import { ThemeModeContext } from '../../theme/M3/providers/ThemeModeProvider';
import { ThemeSchemeContext } from '../../theme/M3/providers/ThemeSchemeProvider';
import CheckIcon from "@mui/icons-material/Check";
import AddIcon from '@mui/icons-material/Add';
import RemoveIcon from '@mui/icons-material/Remove';


interface Settings {
    cur_light_time_yellow: number,
    cur_light_time_green: number,
    cur_light_time_red: number,
    interval_car_spawn_l: number,
    interval_car_spawn_r: number,
    interval_car_spawn_d: number,
    interval_car_spawn_u: number,
    max_speed: number,
    min_speed: number,
    view_range: number,
    cur_adaptivness_light_time: boolean
}

const Settings = () => {
    const [sets, setSets] = useState<Settings>();
    const setLightMode = (value: Boolean) => {
        (async () => {
            setSets((await (await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "adaptive_light_time",
                        value: value
                    })
                })
            ).json()));
        }) ();
    };
    const setRedTime = (value: number) => {
        (async () => {
            setSets((await (await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "light_time",
                        which_light: "red",
                        value: value
                    })
                }
            )).json()));
            console.log(value);
        }) ();
    }
    const setGreenTime = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "light_time",
                        which_light: "green",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setYellowTime = (value: number) => {
        if (sets === undefined) return;
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "light_time",
                        which_light: "yellow",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setSpawningPeriodL = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "interval_car_spawn_l",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setSpawningPeriodR = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "interval_car_spawn_r",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setSpawningPeriodD = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "interval_car_spawn_d",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setSpawningPeriodU = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "interval_car_spawn_u",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setVisionDist = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "view_range",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setMinSpeed = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "speed",
                        edge: "min",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    const setMaxSpeed = (value: number) => {
        (async () => {
            setSets((await (await (
                await fetch("http://localhost:1234/set", {
                    method: 'POST',
                    headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        type : "speed",
                        edge: "max",
                        value: value
                    })
                })
            )).json()) as Settings);
        }) ();
    }
    
    return (
        <>
            <Stack direction="column" spacing={7}>
                <Stack direction="column" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        Traffic light mode
                    </Typography>
                    <ToggleButtonGroup exclusive value={sets?.cur_adaptivness_light_time} onChange={ () => { setLightMode(!(sets?.cur_adaptivness_light_time??true)); }}>
                        <ToggleButton value={false}>
                            {!sets?.cur_adaptivness_light_time ? <CheckIcon sx={{ mr: 1 }} /> : <></>}
                            Static
                        </ToggleButton>
                        <ToggleButton value={true}>
                            {sets?.cur_adaptivness_light_time ? <CheckIcon sx={{ mr: 1 }} /> : <></>}
                            Dynamic
                        </ToggleButton>
                    </ToggleButtonGroup>
                </Stack>
                <Stack direction="row" spacing={30}>
                    <Stack direction="column" spacing={2}>
                        <Typography variant="h6" fontWeight="bold">
                            Time of the red light
                        </Typography>
                        <Stack direction="row" spacing={2}>
                            <Typography variant="h6" fontWeight={ !sets?.cur_adaptivness_light_time ? "bold" : "lighter" }>
                                { sets?.cur_light_time_red }
                            </Typography>
                            <FormControlLabel disabled={ !!sets?.cur_adaptivness_light_time } control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setRedTime(Math.max((sets?.cur_light_time_red??0) - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {

                                        setRedTime((sets?.cur_light_time_red??0) + 1);
                                    }}>
                                        <AddIcon fontSize='small' />
                                    </Button>
                                </ButtonGroup>
                            }/>
                        </Stack>
                    </Stack>
                    <Stack direction="column" spacing={2}>
                        <Typography variant="h6" fontWeight="bold">
                            Time of the yellow light
                        </Typography>
                        <Stack direction="row" spacing={2}>
                            <Typography variant="h6" fontWeight={ !!sets?.cur_adaptivness_light_time ? "bold" : "lighter" }>
                                { sets?.cur_light_time_yellow }
                            </Typography>
                            <FormControlLabel disabled={ !!sets?.cur_adaptivness_light_time } control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setYellowTime(Math.max((sets?.cur_light_time_yellow??0) - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setYellowTime((sets?.cur_light_time_yellow??0) + 1);
                                    }}>
                                        <AddIcon fontSize='small' />
                                    </Button>
                                </ButtonGroup>
                            }/>
                        </Stack>
                    </Stack>
                    <Stack direction="column" spacing={2}>
                        <Typography variant="h6" fontWeight="bold">
                            Time of the green light
                        </Typography>
                        <Stack direction="row" spacing={2}>
                            <Typography variant="h6" fontWeight={ !!sets?.cur_adaptivness_light_time ? "bold" : "lighter" }>
                                { sets?.cur_light_time_green }
                            </Typography>
                            <FormControlLabel disabled={ !!sets?.cur_adaptivness_light_time } control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setGreenTime(Math.max((sets?.cur_light_time_green??0) - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setGreenTime((sets?.cur_light_time_green??0) + 1);
                                    }}>
                                        <AddIcon fontSize='small' />
                                    </Button>
                                </ButtonGroup>
                            }/>
                        </Stack>
                    </Stack>
                </Stack>
                <Typography variant="h6" fontWeight="bold">
                    Period of spawning the new cars on the left
                </Typography>
                <Stack direction="row" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        { sets?.interval_car_spawn_l }
                    </Typography>
                    <FormControlLabel control={
                        <ButtonGroup size='small'>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodL(Math.max((sets?.interval_car_spawn_l??0) - 1, 1));
                            }}>
                                <RemoveIcon fontSize='small' />
                            </Button>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodL((sets?.interval_car_spawn_l??0) + 1);
                            }}>
                                <AddIcon fontSize='small' />
                            </Button>
                        </ButtonGroup>
                    }/>
                </Stack>
                <Typography variant="h6" fontWeight="bold">
                    Period of spawning the new cars on the right
                </Typography>
                <Stack direction="row" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        { sets?.interval_car_spawn_r }
                    </Typography>
                    <FormControlLabel control={
                        <ButtonGroup size='small'>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodR(Math.max((sets?.interval_car_spawn_r??0) - 1, 1));
                            }}>
                                <RemoveIcon fontSize='small' />
                            </Button>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodR((sets?.interval_car_spawn_r??0) + 1);
                            }}>
                                <AddIcon fontSize='small' />
                            </Button>
                        </ButtonGroup>
                    }/>
                </Stack>
                <Typography variant="h6" fontWeight="bold">
                    Period of spawning the new cars on the up
                </Typography>
                <Stack direction="row" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        { sets?.interval_car_spawn_u }
                    </Typography>
                    <FormControlLabel control={
                        <ButtonGroup size='small'>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodU(Math.max((sets?.interval_car_spawn_u??0) - 1, 1));
                            }}>
                                <RemoveIcon fontSize='small' />
                            </Button>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodU((sets?.interval_car_spawn_u??0) + 1);
                            }}>
                                <AddIcon fontSize='small' />
                            </Button>
                        </ButtonGroup>
                    }/>
                </Stack>
                <Typography variant="h6" fontWeight="bold">
                    Period of spawning the new cars on the down
                </Typography>
                <Stack direction="row" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        { sets?.interval_car_spawn_d }
                    </Typography>
                    <FormControlLabel control={
                        <ButtonGroup size='small'>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodD(Math.max((sets?.interval_car_spawn_d??0) - 1, 1));
                            }}>
                                <RemoveIcon fontSize='small' />
                            </Button>
                            <Button size='small' onClick={() => {
                                setSpawningPeriodD((sets?.interval_car_spawn_d??0) + 1);
                            }}>
                                <AddIcon fontSize='small' />
                            </Button>
                        </ButtonGroup>
                    }/>
                </Stack>
                <Typography variant="h6" fontWeight="bold">
                    Range of vision
                </Typography>
                <Stack direction="row" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        { sets?.view_range }
                    </Typography>
                    <FormControlLabel control={
                        <ButtonGroup size='small'>
                            <Button size='small' onClick={() => {
                                setVisionDist(Math.max((sets?.view_range??0) - 1, 1));
                            }}>
                                <RemoveIcon fontSize='small' />
                            </Button>
                            <Button size='small' onClick={() => {
                                setVisionDist((sets?.view_range??0) + 1);
                            }}>
                                <AddIcon fontSize='small' />
                            </Button>
                        </ButtonGroup>
                    }/>
                </Stack>
                <Stack direction="row" spacing={30}>
                    <Stack direction="column" spacing={2}>
                        <Typography variant="h6" fontWeight="bold">
                            Minimal speed
                        </Typography>
                        <Stack direction="row" spacing={2}>
                            <Typography variant="h6" fontWeight="bold">
                                { sets?.min_speed??0 }
                            </Typography>
                            <FormControlLabel control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setMinSpeed(Math.max((sets?.min_speed??0) - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setMinSpeed((sets?.min_speed??0) + 1);
                                    }}>
                                        <AddIcon fontSize='small' />
                                    </Button>
                                </ButtonGroup>
                            }/>
                        </Stack>
                    </Stack>

                    <Stack direction="column" spacing={2}>
                        <Typography variant="h6" fontWeight="bold">
                            Maximal speed
                        </Typography>
                        <Stack direction="row" spacing={2}>
                            <Typography variant="h6" fontWeight="bold">
                                { sets?.max_speed }
                            </Typography>
                            <FormControlLabel control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setMaxSpeed(Math.max((sets?.max_speed??0) - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setMaxSpeed((sets?.max_speed??0) + 1);
                                    }}>
                                        <AddIcon fontSize='small' />
                                    </Button>
           export default Settings;                     </ButtonGroup>
                            }/>
                        </Stack>
                    </Stack>
                </Stack>
            </Stack>
        </>
    );
};

export default Settings;
