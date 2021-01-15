// React imports.
import React from "react";

// App imports.
import { createSocketComm } from "./socketComm";


// Interfaces.
interface ISelectedTile { layer: number, row: number, column: number, type: number }
interface IScores { player: number, opponent: number }


/**
 * This function must be called once and only once from BaseLayout.
 */
export function createState(inParentComponent: React.Component) {

  return {

    // Player and opponent's current score.
    scores : <IScores>{ player : 0, opponent : 0 },

    // The player ID as returned by the server.
    pid : <string>"",

    // The socketComm object used to make server calls.
    socketComm : <Function>createSocketComm(inParentComponent),

    // The time since the player last matched a tile pair.
    timeSinceLastMatch : <number>0,


    // ---------------------------------------- Message Handler Functions ----------------------------------------


    /**
     * Handle 'connected' message.  Occurs when this player connects to the server.
     *
     * @parain inPID The player's ID.
     */
    handleMessage_connected : function(inPID: string) {

      this.setState({ pid : inPID });

    }.bind(inParentComponent), /* End handleMessage_connected(). */


    /**
     * Handle 'start' message.  Occurs when two players have connected to the server.
     *
     * @param inLayout The board layout.
     */
    handleMessage_start: function(inLayout: number[][][]) {

      this.setState({
        timeSinceLastMatch : new Date().getTime(),
        layout : inLayout,
        gameState : "playing"
      });

    }.bind(inParentComponent), /* End handleMessage_start(). */


    /**
     * Handle 'update' message.  Occurs when a player matches a tile pair.
     *
     * @param inPID   The player ID of the player.
     * @param inScore The new score for the player.
     */
    handleMessage_update: function(inPID: string, inScore: number) {

      // This player's score is always up to date, so we only need to update the opponent's score.
      if (inPID !== this.state.pid) {
        const scores: IScores = { ...this.state.scores };
        scores.opponent = inScore;
        this.setState({ scores : scores });
      }

    }.bind(inParentComponent),


    /**
     * Handle 'gameOver' message.  Occurs when both players have each either dead-ended or cleared the board.
     *
     * @param inPID The player ID of the winning player.
     */
    handleMessage_gameOver: function(inPID: string) {

      if (inPID === this.state.pid) {
        this.setState({ gameState : "gameOver", gameOutcome : "**** YOU WON! ****" });
      } else {
        this.setState({ gameState : "gameOver", gameOutcome : "Tough luck, you lost :(" });
      }

    }.bind(inParentComponent),


    // ---------------------------------------- Game Functions ----------------------------------------
    cardClick : function(inRow: number) {
      if (inRow == null) {

      }
      console.log("You cliked!");
      console.log(inRow);

    }.bind(inParentComponent),

    canCardBePlayed : function(): boolean {
      return false;
    }.bind(inParentComponent),

    canAnyCardBePlayed : function(): boolean {
      return false;
    }.bind(inParentComponent),
  };
}