import {Stack, ToggleButton, ToggleButtonGroup, Typography} from '@mui/material';
import React, {useState} from "react";
import CheckIcon from '@mui/icons-material/Check';


const Home = () => {

    const [alignment, setAlignment] = useState<string | null>('dynamic');

    const handleAlignment = (
        _event: React.MouseEvent<HTMLElement>,
        newAlignment: string | null,
    ) => {
        setAlignment(newAlignment);
    };

    return (
        <>
        </>
    );
};

export default Home;