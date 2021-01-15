import React, { ReactElement } from "react";

const PlayerBoard = ({ state }: any) => {
    const hand: ReactElement[] = [];

    for (let r: number = 0; r < state.hand.length; r++) {
        hand.push(
            <img
                className="card"
                src={'./img/2_of_clubs.svg'}
                onClick={() => state.cardClick(r)}
                alt=""
            />
        );
    }

    return <React.Fragment>{hand}</React.Fragment>;
};

export default PlayerBoard;
