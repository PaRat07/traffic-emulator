import { Box, Drawer, DrawerProps, List, ListItem, ListItemButton, ListItemIcon, ListItemText, Toolbar, Typography } from "@mui/material";
import { FC, useState, useEffect } from 'react';

import { Link, useLocation } from "react-router-dom";

import HomeIcon from '@mui/icons-material/Home';
import HomeIconOutlined from '@mui/icons-material/HomeOutlined';

import SettingIconOutlined from "@mui/icons-material/SettingsOutlined";
import SettingIconFilled from "@mui/icons-material/Settings";

const MainDrawer: FC<DrawerProps> = (props) => {
    const { onClose, ...others } = props;

    const location = useLocation();
    const [selectedIndex, setSelectedIndex] = useState(location.pathname.replace('/', ''));

    useEffect(() => {
        setSelectedIndex(location.pathname.replace('/', ''));
    }, [location.pathname])


    const handleListItemClick = (index: string) => {
        setSelectedIndex(index);
        onClose?.({}, 'backdropClick');
    };
    return (
        <Drawer {...others} onClose={onClose}>
            <Toolbar >
                <Typography color="inherit" sx={{ fontWeight: 500, letterSpacing: 0.5, fontSize: 20 }}>
                    Material You
                </Typography>
            </Toolbar>
            <List >
                <Box>
                    <ListItem >
                        <ListItemButton component={Link} to='/Home' selected={selectedIndex == 'Home'} onClick={() => handleListItemClick('Home')}>
                            <ListItemIcon>
                                {selectedIndex == 'Home' ? <HomeIcon /> : <HomeIconOutlined />}
                            </ListItemIcon>
                            <ListItemText>Home</ListItemText>
                        </ListItemButton>
                    </ListItem>
                    <ListItem >
                        <ListItemButton component={Link} to='/Settings' selected={selectedIndex == 'ColorSystem'} onClick={() => handleListItemClick('ColorSystem')}>
                            <ListItemIcon>
                                {selectedIndex == 'ColorSystem' ? <SettingIconFilled/> : <SettingIconOutlined/>}
                            </ListItemIcon>
                            <ListItemText>Settings</ListItemText>
                        </ListItemButton>
                    </ListItem>
                    {/*<ListItem >
                        <ListItemButton component={Link} to='/About' selected={selectedIndex == 'About'} onClick={() => handleListItemClick('About')}>
                            <ListItemIcon>
                                {selectedIndex == 'About' ? <InfoIcon /> : <InfoIconOutlined />}
                            </ListItemIcon>
                            <ListItemText>About</ListItemText>
                        </ListItemButton>
                    </ListItem>*/}
                </Box>
            </List>
        </Drawer>
    );
};

export default MainDrawer;