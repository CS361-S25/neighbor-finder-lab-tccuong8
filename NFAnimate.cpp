#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/math.hpp"

emp::web::Document doc{"target"};

class NFAnimator : public emp::web::Animate {
    // First you need to create an instance variable in your NFAnimator class that will be your canvas: 
    emp::web::Canvas canvas{2500, 2500, "canvas"};
    // The first two arguments are the width and height and the third argument is the HTML id (don’t worry if you don’t know what that means, we aren’t going to need it).

    // define a constructor for your class and have your canvas placed into your doc:
    
    public: 
        // Global CA-defining vars
        int gridSize = 10;
        int cellSize = 50;

        NFAnimator() {
            // Anytime you want to add things to the webpage that you are making, you will use this syntax.
            doc << canvas;
            // doc << "Hi";

            // Empirical makes it easy to draw your typical shapes on the canvas. To draw a rectangle, you just need to call Canvas’ Rect method: 
            // The first two arguments are the x and y coordinates for the upper left corner (0,0 in this case), the next two arguments are the width and height of your rectangle (10 x 10 in this case), the next argument is the fill color, and the final argument is the line color. All the typical colors are supported, so feel free to play around making a more colorful rectangle!
            // canvas.Rect(0, 0, 10, 10, "white", "black");

            // Make a grid for the CA
            for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                    canvas.Rect(i*cellSize, j*cellSize, cellSize, cellSize, "white", "black");
                }
            }
        }

        // You’re now ready to find some neighbors! Create a new method void FindNeighbors(x, y) that:
        // 1. Sets the color of the x,y cell to black (just make a new rectangle at the correct location, you can’t easily change the color of the existing one).
        // 2. Calculates each of the x,y cell’s neighbors and sets them to a different color, for example red.

        void FindNeighbors(int x, int y){
            // Set the color of the x,y cell to black
            canvas.Rect(x*cellSize, y*cellSize, cellSize, cellSize, "black", "black");

            // Calculate each of the x,y cell's neighbors and set them to a different color
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue; // Skip the center cell
                    // Use modulus to wrap around the grid
                    int neighborX = emp::Mod((x + i), gridSize);
                    int neighborY = emp::Mod((y + j), gridSize);
                    canvas.Rect(neighborX*cellSize, neighborY*cellSize, cellSize, cellSize, "red", "black");
                }
            }
        }

};

NFAnimator animator;

int main() {
    animator.Step();
    animator.FindNeighbors(0, 0);
}