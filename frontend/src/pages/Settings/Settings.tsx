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

enum TrafficLightMode {
    STATIC = 'STATIC',
    DYNAMIC = 'DYNAMIC'
}

const Settings = () => {

    // const { themeScheme } = useContext(ThemeSchemeContext);
    // const { themeMode } = useContext(ThemeModeContext);
    // const light = themeScheme[themeMode];

    const [lightMode, setLightMode] = useState<TrafficLightMode>(TrafficLightMode.STATIC);
    const [spawningPeriod, setSpawningPeriod] = useState<number>(3);
    const [redTime, setRedTime] = useState<number>(3);
    const [yellowTime, setYellowTime] = useState<number>(3);
    const [greenTime, setGreenTime] = useState<number>(3);
    const [visionDist, setVisionDist] = useState<number>(3);
    const [minSpeed, setMinSpeed] = useState<number>(3);
    const [maxSpeed, setMaxSpeed] = useState<number>(3);

    // const [alignment, setAlignment] = useState<string | null>('dynamic');
    //
    // const handleAlignment = (
    //     _event: React.MouseEvent<HTMLElement>,
    //     newAlignment: string | null,
    // ) => {
    //     setAlignment(newAlignment);
    // };

    return (
        <>
            <Stack direction="column" spacing={7}>
                <Stack direction="column" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        Traffic light mode
                    </Typography>
                    <ToggleButtonGroup exclusive value={lightMode} onChange={ () => { setLightMode(lightMode === TrafficLightMode.STATIC ? TrafficLightMode.DYNAMIC : TrafficLightMode.STATIC); }}>
                        <ToggleButton value={TrafficLightMode.STATIC}>
                            {lightMode === TrafficLightMode.STATIC ? <CheckIcon sx={{ mr: 1 }} /> : <></>}
                            Static
                        </ToggleButton>
                        <ToggleButton value={TrafficLightMode.DYNAMIC}>
                            {lightMode === TrafficLightMode.DYNAMIC ? <CheckIcon sx={{ mr: 1 }} /> : <></>}
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
                            <Typography variant="h6" fontWeight={ lightMode === TrafficLightMode.STATIC ? "bold" : "lighter" }>
                                { redTime }
                            </Typography>
                            <FormControlLabel disabled={ lightMode === TrafficLightMode.DYNAMIC } control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setRedTime(Math.max(redTime - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setRedTime(redTime + 1);
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
                            <Typography variant="h6" fontWeight={ lightMode === TrafficLightMode.STATIC ? "bold" : "lighter" }>
                                { yellowTime }
                            </Typography>
                            <FormControlLabel disabled={ lightMode === TrafficLightMode.DYNAMIC } control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setYellowTime(Math.max(yellowTime - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setYellowTime(yellowTime + 1);
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
                            <Typography variant="h6" fontWeight={ lightMode === TrafficLightMode.STATIC ? "bold" : "lighter" }>
                                { greenTime }
                            </Typography>
                            <FormControlLabel disabled={ lightMode === TrafficLightMode.DYNAMIC } control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setGreenTime(Math.max(greenTime - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setGreenTime(greenTime + 1);
                                    }}>
                                        <AddIcon fontSize='small' />
                                    </Button>
                                </ButtonGroup>
                            }/>
                        </Stack>
                    </Stack>
                </Stack>
                <Typography variant="h6" fontWeight="bold">
                    Period of spawning the new cars
                </Typography>
                <Stack direction="row" spacing={2}>
                    <Typography variant="h6" fontWeight="bold">
                        { spawningPeriod }
                    </Typography>
                    <FormControlLabel disabled={ spawningPeriod === 2 } control={
                        <ButtonGroup size='small'>
                            <Button size='small' onClick={() => {
                                setSpawningPeriod(Math.max(spawningPeriod - 1, 1));
                            }}>
                                <RemoveIcon fontSize='small' />
                            </Button>
                            <Button size='small' onClick={() => {
                                setSpawningPeriod(spawningPeriod + 1);
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
                        { visionDist }
                    </Typography>
                    <FormControlLabel control={
                        <ButtonGroup size='small'>
                            <Button size='small' onClick={() => {
                                setVisionDist(Math.max(visionDist - 1, 1));
                            }}>
                                <RemoveIcon fontSize='small' />
                            </Button>
                            <Button size='small' onClick={() => {
                                setVisionDist(visionDist + 1);
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
                                { minSpeed }
                            </Typography>
                            <FormControlLabel control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setMinSpeed(Math.max(minSpeed - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setMinSpeed(minSpeed + 1);
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
                                { maxSpeed }
                            </Typography>
                            <FormControlLabel control={
                                <ButtonGroup size='small'>
                                    <Button size='small' onClick={() => {
                                        setMaxSpeed(Math.max(maxSpeed - 1, 1));
                                    }}>
                                        <RemoveIcon fontSize='small' />
                                    </Button>
                                    <Button size='small' onClick={() => {
                                        setMaxSpeed(maxSpeed + 1);
                                    }}>
                                        <AddIcon fontSize='small' />
                                    </Button>
                                </ButtonGroup>
                            }/>
                        </Stack>
                    </Stack>
                </Stack>
            </Stack>
        </>
    );
};

export default Settings;