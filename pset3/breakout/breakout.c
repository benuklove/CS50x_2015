//
// breakout.c
//
// Ben Love
// benuklove@gmail.com
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400.0

// height and width of paddle
#define PHEIGHT 5
#define PWIDTH 50

// number of rows of bricks
#define ROWS 5

// space between bricks
#define SPACE 4.0

// changeable number of columns of bricks
#define COLS 10.0

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initGameover(GWindow window);
GLabel initWin(GWindow window);
void updateScoreboard(GWindow window, GLabel scoreboard, int points);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow window, GObject brick);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel scoreboard = initScoreboard(window);
    
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // listen forever
        while (true)
        {
            // listen for mouse event
            GEvent event = getNextEvent(MOUSE_EVENT);
            
            // if there is one
            if (event != NULL)
            {
                // if it's a mouse click
                if (getEventType(event) == MOUSE_CLICKED)
                {
                    // random initial horizontal velocity using cosine/radians
                    double velocit_y = 2.0;
                    double velocit_x = cos(6.28 * drand48()) * 1.5;
                    while (true)
                    {
                        // collision code
                        GObject object = detectCollision(window, ball);
                        if (object == NULL)
                        {
                            // pass
                        }
                        
                        // ball and brick/paddle interaction
                        else if (strcmp(getType(object), "GRect") == 0)
                        {
                            if (object != paddle)
                            {
                                removeGWindow(window, object);
                                points += 1;
                                updateScoreboard(window, scoreboard, points);
                                
                                // game is won
                                if (points == bricks)
                                {
                                    GLabel win = newGLabel("YOU WIN!!!");
                                    setFont(win, "URW Palladio L-48");
                                    double x = (WIDTH - getWidth(win)) / 2;
                                    double y = (HEIGHT - getFontAscent(win)) 
                                                / 2 - 70;
                                    setLocation(win, x, y);
                                    add(window, win);
                                    printf("You won!\n");
                                    return (false);
                                }
                            }
                            velocit_y = -velocit_y;
                        }
                        
                        // ball and wall interaction
                        move(ball, velocit_x, velocit_y);
                        if (getY(ball) <= 0)
                        {
                            velocit_y = -velocit_y;
                        }
                        
                        // open bottom wall with lives lost and game over
                        else if (getY(ball) >= HEIGHT)
                        {
                            lives = lives - 1;
                            setLocation(ball, WIDTH / 2 - RADIUS, 
                                              HEIGHT / 2 - RADIUS);
                            if (lives == 0)
                            {
                                GLabel gameover = newGLabel("GAME OVER");
                                setFont(gameover, "URW Chancery L-48");
                                double x = (WIDTH - getWidth(gameover)) / 2;
                                double y = (HEIGHT - getFontAscent(gameover)) 
                                            / 2 - 70;
                                setLocation(gameover, x, y);
                                add(window, gameover);
                                printf("You lose!\n");
                                return (false);
                            }
                            waitForClick();
                            move(ball, velocit_x, velocit_y);
                        }
                        else if (getX(ball) + (RADIUS * 2) >= WIDTH)
                        {
                            velocit_x = -velocit_x;
                        }
                        else if (getX(ball) <= 0)
                        {
                            velocit_x = -velocit_x;
                        }

                        pause(10);
                        
                        // paddle tracking with mouse
                        GEvent event1 = getNextEvent(MOUSE_EVENT);
                        if (event1 != NULL)
                        {
                            if (getEventType(event1) == MOUSE_MOVED)
                            {
                                double px = getX(event1) - getWidth(paddle) 
                                            / 2;
                                setLocation(paddle, px, 525);
                            }
                        }
                    }    
                }
            }    
        }
    }    

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            float bwidth = (WIDTH / COLS) - ((COLS * SPACE + SPACE) / COLS);
            float x = i * (bwidth + SPACE) + SPACE;
            float bheight = 10;
            float y = j * (bheight + SPACE) + (8 * SPACE);
            GRect brick = newGRect(x, y, bwidth, bheight);
            setFilled(brick, true);
            switch (j)
            {
                case 0:
                    setColor(brick, "8B0000");
                    break;
                case 1:
                    setColor(brick, "DC143C");
                    break;
                case 2:
                    setColor(brick, "FF0000");
                    break;
                case 3:
                    setColor(brick, "FF6347");
                    break;
                case 4:
                    setColor(brick, "FA8072");
                    break;
                default:
                    setColor(brick, "000000");
                    break;
            }
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double x = (WIDTH / 2) - (RADIUS);
    double y = (HEIGHT / 2) - (RADIUS);
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(175, 525, PWIDTH, PHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("0");
    setFont(scoreboard, "Calibri-18");
    double x = (WIDTH - getWidth(scoreboard)) / 2;
    double y = (HEIGHT - getFontAscent(scoreboard)) / 2 - 40;
    setLocation(scoreboard, x, y);
    add(window, scoreboard);
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel scoreboard, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(scoreboard, s);

    // center label in window
    double x = (getWidth(window) - getWidth(scoreboard)) / 2;
    double y = (getHeight(window) - getFontAscent(scoreboard)) / 2 - 40;
    setLocation(scoreboard, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
