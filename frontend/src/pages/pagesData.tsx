import { routerType } from "../types/router.types";
import Settings from "./Settings/Settings.tsx";
import Home from "./Home/Home";

const pagesData: routerType[] = [
    {
        path: "Home",
        element: <Home />,
        title: "Home",
    },
    {
        path: "Settings",
        element: <Settings />,
        title: "Settings"
    }
];

export default pagesData;