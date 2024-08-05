#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <string>

void init (void) 
{ 
    //set's outside the box color
    glClearColor(0.529, 0.808, 0.808, 1.0);
} 

void writeCharacter(int n, char* word){
    for(int i = 0; i < n; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]);
    };
}

char project[] = "Digital Clock";
char name[] = "Amrit Pandey";
char id[] = "78BCT003";
char format[] = "HH  MM SS"; 

char hh_mm_ss[10] = "00:00:00";
char date[]= "2017 12 25";
const float colorChangeSpeed = 0.01f;
float colorList[11] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.0};

void timer(int){
    time_t now = time(0);
    char* dt = ctime(&now);

    date[0] = dt[0];
    date[1] = dt[1];
    date[2] = dt[2];
    date[3] = dt[3];
    date[4] = dt[4];
    date[5] = dt[5];
    date[6] = dt[6];
    date[7] = dt[7];
    date[8] = dt[8];
    date[9] = dt[9];
    date[10] = dt[10];

    hh_mm_ss[0] = dt[11];
    hh_mm_ss[1] = dt[12];
    hh_mm_ss[2] = dt[13];
    hh_mm_ss[3] = dt[14];
    hh_mm_ss[4] = dt[15];
    hh_mm_ss[5] = dt[16];
    hh_mm_ss[6] = dt[17];
    hh_mm_ss[7] = dt[18];

    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void updateColor(float* color, int index){
    for (int i = 0; i < 9; ++i) {
        color[i+index] += colorChangeSpeed;
        if (color[i+index] > 1.0f) color[i+index] = 0.0f; // Reset color if it exceeds 1.0
    }
}

void update(int value) {
    // Update colors gradually
    updateColor(colorList, 1);
    updateColor(colorList, 2);
    updateColor(colorList, 3);
    updateColor(colorList, 4);

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(600, update, 0); // Call update again after 16 milliseconds (about 60 FPS)
}


void display (void)  
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity();

// big rectangle
    glBegin(GL_POLYGON);
     glColor3f(colorList[0], colorList[1], colorList[2]); glVertex2f(5.0, 5.0);
     glColor3f(colorList[3], colorList[4], colorList[5]); glVertex2f(-5.0, 5.0);
     glColor3f(colorList[6], colorList[7], colorList[8]); glVertex2f(-5.0, -5.0);
     glColor3f(colorList[9], colorList[10], colorList[2]); glVertex2f(5.0, -5.0);
    glEnd();


    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
     glVertex2f(2, 2);
     glVertex2f(-2, 2);
     glVertex2f(-2, -2);
     glVertex2f(2, -2);
    glEnd();

    glColor3f(0.0, 0.2, 0.4);
    
    // display time format hh mm ss
    glRasterPos2f(-0.62, 0.6);
    for(int i = 0; i < 12; i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, format[i]);
    };

    // display time
    glRasterPos2f(-0.62, -0.14);
    writeCharacter(8, hh_mm_ss);
    
    //display date
    glRasterPos2f(-0.72, -1.0);
    writeCharacter(11, date);

    // Display Project name
    glRasterPos2f(-9, -7);
    writeCharacter(13, project);

    //display author name
    glRasterPos2f(-9, -8);
    writeCharacter(12, name);

    //display author id
    glRasterPos2f(-9, -9);
    writeCharacter(8, id);

    glutSwapBuffers(); // due to animation 

}; 

void reshape(int w, int h){
    glViewport(0,0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
};

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Graphics project");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  //for animation after 1000ms the timer func is called
  glutTimerFunc(1000, timer, 0);
  glutTimerFunc(16, update, 0);

  glutMainLoop();
};