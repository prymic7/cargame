
#include <raylib.h>
#include <iostream>
// #include <deque>
#include <raymath.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <sstream>
#include "rlgl.h"
// #include <ctime>

int screenWidth = 900;
int screenHeight = 1150;

class Car { 

public:
    Image image = LoadImage("img/tankcar.png");
    Image imageMenu = LoadImage("img/tankcarMenu.png");
    Image image2 = LoadImage("img/monstertruck.png");
    Image image2Menu = LoadImage("img/monstertruckMenu.png");
    Image image3 = LoadImage("img/dumpstercar.png");
    Image image3Menu = LoadImage("img/dumpstercarMenu.png");
    Texture2D texture = LoadTextureFromImage(image);
    Texture2D texture2 = LoadTextureFromImage(image2);
    Texture2D texture3 = LoadTextureFromImage(image3);
    Texture2D texture3Menu = LoadTextureFromImage(image3Menu);
    Texture2D textureMenu = LoadTextureFromImage(imageMenu);
    Texture2D texture2Menu = LoadTextureFromImage(image2Menu);
    int carX = 400;
    int carY = 950;
    int speedOfCar = 4;
    std::vector<Texture2D> carTextures = {textureMenu, texture2Menu, texture3Menu};
    std::vector<Texture2D> carPlayTextures = {texture, texture2, texture3};
    
    
    ~Car(){
        UnloadImage(image);
        UnloadImage(imageMenu);
        UnloadImage(image2);
        UnloadImage(image2Menu);
        UnloadImage(image3);
        UnloadImage(image3Menu);

        UnloadTexture(texture);
        UnloadTexture(texture2);
        UnloadTexture(texture3);
        UnloadTexture(textureMenu);
        UnloadTexture(texture2Menu);
        UnloadTexture(texture3Menu);
    }

    std::vector<Texture2D> returnTextures(){
        return carTextures;
    }

    std::vector<Texture2D> returnPlayTextures(){
        return carPlayTextures;
    }

    void update(){
        checkXBorder();
    }

    int getSpeedCar(){
        return speedOfCar;
    }

    void updateCoordinates(char letter, int num, char letter2 = 'o', int num2 = 0){
        if(letter == 'x' && letter2 == 'o'){
            carX += num;
        } else if(letter == 'y' && letter2 == 'o'){
            carY += num;
        } else if(letter == 'y' && letter2 == 'x'){
            carY += num;
            carX += num2;
        }
    }

    std::vector<int> getPos(){
        std::vector<int> position = {carX, carY};
        return position;
    }

    std::vector<int> getImageSize(){
        std::vector<int> size = {image.width, image.height};
        return size;
    }

    void setDefaultPos(){
        carX = 400;
        carY = 950;
    }

    bool checkXBorder(){
        std::vector<int> position = getPos();
        if(position[0] < 50 || position[0] > 600){
            return true;
        }
        return false;
    }
};

class Barrier{
public:  
    Texture2D texture;
    Image image;
    int posX;
    int posY = -65;
    double barrierSpeed = 12;
    static Image imageArray[5];
    static Texture2D textureArray[5];
    bool crashed = false;
    

    Barrier(int xSpawn){
        int randomNumber = rand() % 5;
        posX = xSpawn;
        image = imageArray[randomNumber];
        texture = textureArray[randomNumber];
    }


    ~Barrier(){
        UnloadImage(image);
        UnloadTexture(texture);
        
    }

    bool returnStatus(){
        return crashed;
    }

    void setStatus(bool co){
        crashed = co;
    }

    Texture2D getTexture(){
        return texture;
    }

    Image getImage(){
        return image;
    }

    void update(){
        moveBarrier();
    }

    void draw(){
        
        drawCar();
    }

    void drawCar(){
        DrawTexture(texture, posX, posY, WHITE);  
    }


    std::vector<int> getPos(){
        std::vector<int> positions = {posX, posY};
        return positions;
    }

    void moveBarrier(){
        if(crashed){
            posY += 10;
        } else if(!crashed){
            posY += barrierSpeed;
        }
        
        
    }

    std::vector<int> getImageSize(){
        std::vector<int> size = {image.width, image.height};
        return size;

    }

    double getSpeedOfBarrier(){
        return barrierSpeed;
    }

    void updateSpeedOfBarrier(double num){
        barrierSpeed += num;
    }

};

Image Barrier::imageArray[5] = { nullptr };
Texture2D Barrier::textureArray[5] = { 0 };

void InitializeBarrierArrays() {
    Barrier::imageArray[0] = LoadImage("img/bluecar.png");
    Barrier::imageArray[1] = LoadImage("img/greencar.png");
    Barrier::imageArray[2] = LoadImage("img/lightbluecar.png");
    Barrier::imageArray[3] = LoadImage("img/purplecar.png");
    Barrier::imageArray[4] = LoadImage("img/redcar.png");

    Barrier::textureArray[0] = LoadTextureFromImage(Barrier::imageArray[0]);
    Barrier::textureArray[1] = LoadTextureFromImage(Barrier::imageArray[1]);
    Barrier::textureArray[2] = LoadTextureFromImage(Barrier::imageArray[2]);
    Barrier::textureArray[3] = LoadTextureFromImage(Barrier::imageArray[3]);
    Barrier::textureArray[4] = LoadTextureFromImage(Barrier::imageArray[4]);
}

void UnloadBarrierArrays() {
    for (int i = 0; i < 5; ++i) {
        UnloadImage(Barrier::imageArray[i]);
        UnloadTexture(Barrier::textureArray[i]);
    }
}


class Menu {
public:

    int menuWidth = 600;
    int menuHeight = 800;
    int buttonWidth = 450;
    int buttonHeight = 150;
    

    bool menuSeen = true;
    bool startGame = false;
    std::chrono::system_clock::time_point time_start = std::chrono::system_clock::now();
    float rotationSpeed = 180.0f;
    float carRotation = 0.0f;
    float finalRotation = 180.0f;
    float rotation = 0.0f;
    bool restartGame = false;
    Image menuImg = LoadImage("img/menuimg.png");
    Image rightArrowImg = LoadImage("img/rightarrow.png");
    Image leftArrowImg = LoadImage("img/leftarrow.png");
    Texture2D menuTexture = LoadTextureFromImage(menuImg);
    Texture2D leftArrowTexture = LoadTextureFromImage(leftArrowImg);
    Texture2D rightArrowTexture = LoadTextureFromImage(rightArrowImg);
    Color menuColor = {51, 51, 51, 255};
    bool mainMenuSeen = true;
    bool chooseCarSeen = false;
    int pageNum = 0;
    Car car;
    std::vector<Texture2D> carTextures = car.returnTextures();
    int carNum = carTextures.size();
    Vector2 imagePos = {50, 50};

    Rectangle menuRectangle = {(float)screenWidth/2 - menuWidth/2, (float)screenHeight/2 - menuHeight/2, (float)menuWidth, (float)menuHeight};
    Rectangle buttonRectangle = { (float)menuRectangle.x + menuRectangle.width / 2 - buttonWidth / 2, (float)menuRectangle.y + 180 / 2 - buttonHeight / 2, (float)buttonWidth, (float)buttonHeight };
    Rectangle buttonRectangle2 = { (float)menuRectangle.x + menuRectangle.width / 2 - buttonWidth / 2, (float)(menuRectangle.y + 180 / 2 - buttonHeight / 2) + (buttonRectangle.height + 60), (float)buttonWidth, (float)buttonHeight};
    Rectangle arrowLeftRectangle = {(float)menuRectangle.x + 5, (float)menuRectangle.height/2 + menuRectangle.y - 40, (float)80, (float)80};
    Rectangle arrowRightRectangle = {(float)(menuRectangle.x + menuRectangle.width) -rightArrowTexture.width-5, (float)menuRectangle.height/2 + menuRectangle.y - 40, (float)80, (float)80};
    Rectangle backButtonRectangle = {50.0, 50.0, 150.0, 50.0};


    ~Menu(){
        UnloadTexture(menuTexture);
        UnloadTexture(leftArrowTexture);
        UnloadTexture(rightArrowTexture);

        UnloadImage(menuImg);
        UnloadImage(rightArrowImg);
        UnloadImage(leftArrowImg);
    }

    bool returnRestartGame(){
        return restartGame;
    }


    void setRestartGame(bool co){
        restartGame = co;
    }

    int returnChosenCar(){
        return pageNum;
    }

    bool isMenuSeen(){
        return menuSeen;
    }

    bool menuStartGame(){
        return startGame;
    }

    void menuSeenSet(bool co){
        menuSeen = co;
    }

    void menuStartGameSet(bool co){
        startGame = co;
    }

    void displayImg(){
        DrawTexture(menuTexture, 50, 650, WHITE);
    }

    void draw(){
        
         DrawRectangle((float)menuRectangle.x, (float)menuRectangle.y, (float)menuRectangle.width, (float)menuRectangle.height, menuColor);
        if(mainMenuSeen){
           
            DrawRectangle((float)buttonRectangle.x, (float)buttonRectangle.y + 30, (float)buttonRectangle.width, (float)buttonRectangle.height, ORANGE);
            DrawRectangle((float)buttonRectangle.x, (float)buttonRectangle.y + (buttonRectangle.height + 60), (float)buttonRectangle.width, (float)buttonRectangle.height, ORANGE);
            DrawText("Play Game", buttonRectangle.x + 100, buttonRectangle.y + 80, 50, WHITE);
            DrawText("Change Car", buttonRectangle.x + 80, buttonRectangle.y + 260, 50, WHITE);
            displayImg();
        } else if(chooseCarSeen){
            DrawRectangle((float)50, (float)50, (float)150, (float)50, ORANGE);
            DrawText("Back", 85, 60, 35, WHITE);
            DrawTexture(carTextures[pageNum], (menuRectangle.width/2 + menuRectangle.x) - carTextures[pageNum].width/2, menuRectangle.height/2 + menuRectangle.y - carTextures[pageNum].height/2, WHITE);
            DrawTexture(leftArrowTexture, menuRectangle.x + 5, menuRectangle.height/2 + menuRectangle.y - 40, WHITE);
            DrawTexture(rightArrowTexture, menuRectangle.x + menuRectangle.width - rightArrowTexture.width - 5, menuRectangle.height/2 + menuRectangle.y - 40, WHITE);
            // DrawRectangle(menuRectangle.width/2 + menuRectangle.x, menuRectangle.height/2 + menuRectangle.y, 20, 20, RED);
            
        }
        

    }

    void update(){
        checkUserInput();
    }

    void checkUserInput(){

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            
            if (CheckCollisionPointRec(GetMousePosition(), buttonRectangle2)) {
                mainMenuSeen = false;
                chooseCarSeen = true;    
            }  
            if (CheckCollisionPointRec(GetMousePosition(), backButtonRectangle)) {
                mainMenuSeen = true;
                chooseCarSeen = false;      
            } 
            if (CheckCollisionPointRec(GetMousePosition(), buttonRectangle)) {
                menuSeen = false;
                startGame = true;
                setRestartGame(true);  
            } 
            if (CheckCollisionPointRec(GetMousePosition(), arrowLeftRectangle)) {
                if(pageNum > 0){
                    pageNum--;
                }
            } 
            if (CheckCollisionPointRec(GetMousePosition(), arrowRightRectangle)) {
                if(pageNum < carNum-1){ 
                    pageNum++;
                }
            } 
        }  
    }
};


class Game { 
public:
    Menu menu;
    Car car = Car();

    std::vector<Texture2D> allCars = car.returnPlayTextures();
    int pageNum;
    Image image1 = LoadImage("img/road.png");
    Image image3 = LoadImage("img/helicopter1.png");
    Image image4 = LoadImage("img/helicopter2.png");
    Image image5 = LoadImage("img/jet1.png");
    Image image6 = LoadImage("img/jet2.png");
    Image heartFull = LoadImage("img/heartFull.png");
    Image heartEmpty = LoadImage("img/heartEmpty.png");
    Image policeCarImage = LoadImage("img/policecar.png");
    Image afterExplosionImage = LoadImage("img/afterExplosion.png");
    Image policeCirclesImg = LoadImage("img/policecircles.png");
    Image smallHeartImg = LoadImage("img/smallheart.png");
    Image bluredMajakBlueImg = LoadImage("img/bluredmajakblue.png");
    Image bluredMajakRedImg = LoadImage("img/bluredmajakred.png");
    
    Texture2D texture1 = LoadTextureFromImage(image1);
    Texture2D texture3 = LoadTextureFromImage(image3);
    Texture2D texture4 = LoadTextureFromImage(image4);
    Texture2D texture5 = LoadTextureFromImage(image5);
    Texture2D texture6 = LoadTextureFromImage(image6);
    Texture2D heartFull_texture = LoadTextureFromImage(heartFull);
    Texture2D heartEmpty_texture = LoadTextureFromImage(heartEmpty);
    Texture2D policeCarTexture = LoadTextureFromImage(policeCarImage);
    Texture2D afterExplosionTexture = LoadTextureFromImage(afterExplosionImage);
    Texture2D policeCirclesTexture = LoadTextureFromImage(policeCirclesImg);
    Texture2D smallHeartTexture = LoadTextureFromImage(smallHeartImg);
    Texture2D bluredMajakBlueTexture = LoadTextureFromImage(bluredMajakBlueImg);
    Texture2D bluredMajakRedTexture = LoadTextureFromImage(bluredMajakRedImg);


    Sound sound1 = LoadSound("audio/helicopterSound.mp3");
    Sound sound2 = LoadSound("audio/crash.mp3");
    Sound policeSiren = LoadSound("audio/policeSiren.mp3");
    int lives = 3;
    int score = 0;
    int againCount = 0;
    bool animationRunning = false;
    int roadYInt1 = -1150;
    int roadYInt2 = -3470;
    int heartY = -10;
    int luckyNumHeartX;
    int speedOfAnimation = 10;
    std::vector<int> imagesRoadY;
    std::vector<Barrier*> barriersVec = {};
    std::vector<Texture2D> heartsVec = {};
    bool catching = false;
    bool backing = false;
    bool isAnimationRunning = false;
    int restartAnimationCount;
    bool restart = false;
    bool canMove = false;
    std::chrono::system_clock::time_point restartCount = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point codeExecutedRestart = std::chrono::system_clock::now();;
    std::chrono::system_clock::time_point runningAnimation;
    std::chrono::system_clock::time_point catching_end;
    std::chrono::system_clock::time_point backing_already;
    std::chrono::system_clock::time_point crashOrCheck = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point scoreTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point twoCloseCollisionStart = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point twoCloseCollision = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point lifeAddedTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point majakyTime = std::chrono::system_clock::now();
    bool continueCode = false;
    bool codeExecuted = false;
    bool executeCode1 = false;
    bool crashBool = false;
    bool pause = false;
    bool gameRestarted = false;
    bool lifeAdded = false;

    //final animation
    // std::ostringstream finalText;
    
    
    // std::string finalTextStr = finalText.str();

    std::chrono::system_clock::time_point timeToMenuStart;
    std::chrono::system_clock::time_point timeToMenuNow;
    std::chrono::system_clock::time_point gameRestartedTime;
    std::chrono::system_clock::time_point startFinalAnimation;
    std::chrono::system_clock::time_point lastHeart = std::chrono::system_clock::now();

    bool finalAnimation = false;
    float rotationSpeedLeft1 = 180.0f;
    float rotationSpeedLeft2 = 180.0f;
    float rotationSpeedRight1 = 180.0f;
    float rotationSpeedPolice1 = 180.0f;
    float rotationSpeedPolice2 = 180.0f;

    float carRotationLeft1 = 0.0f;
    float carRotationLeft2 = 0.0f;
    float carRotationRight1 = 0.0f;
    float policeRotationRight1 = 0.0f;
    float policeRotationRight2 = 0.0f;

    float finalRotationLeft1 = 90.0f;
    float finalRotationLeft2 = 160.0f;
    float finalRotationRight1 = -110.0f;
    float finalRotationPolice1 = -60.0f;
    float finalRotationPolice2 = 0.0f;
    float rotation = 0.0f;
    
    int majakyRotationX = 0;
    int majakyRotationY = 0;
    float policeCarsY = 1000;

    Vector2 posOfTheCarAfterCrash;

    Vector2 helicopter1vec = {170, policeCarsY};
    Vector2 helicopter2vec = {80, policeCarsY};
    Vector2 jet1vec = {350, policeCarsY};
    Vector2 helicopter1vec2 = {550, policeCarsY};
    Vector2 jet2vec = {700, policeCarsY};
    Vector2 police1vec = {550, policeCarsY + 100};
    Vector2 police2vec = {650, policeCarsY + 100};

    int police1xNow = 0;
    int police2xNow = 0;
    int police1yNow = 0;
    int police2yNow = 0;

    int countToStopMovingY = 0;

    //after collision
    std::vector<Vector2> afterCollisionPos;
    int countCollision = 0;

    //After Death Menu
    
    int button1Width = 350;
    int button1Height = 100;
    int button2Width = 350;
    int button2Height = 100;
    int rect1Width = 400;
    int rect1Height = 90 + button1Height + button2Height;
    Rectangle rectMain = {(float)screenWidth/2-rect1Width/2, (float)screenHeight/2-rect1Height/2, (float)rect1Width, (float)rect1Height};
    Rectangle rectPlayAgain = {(float)rectMain.x +((rectMain.width-button1Width)/2), (float)rectMain.y + 30, (float)button1Width, (float)button1Height};
    Rectangle rectGoMenu = {(float)rectMain.x +((rectMain.width-button1Width)/2), (float)rectPlayAgain.y + button1Height + 30, (float)button2Width, (float)button2Height};

    
    
    
    

    Game(){
        imagesRoadY.push_back(roadYInt1);
        imagesRoadY.push_back(roadYInt2);
    }
    
    
   

    ~Game(){
        UnloadTexture(texture1);
        UnloadTexture(texture3);
        UnloadTexture(texture4);
        UnloadTexture(texture5);
        UnloadTexture(texture6);
        UnloadTexture(heartEmpty_texture);
        UnloadTexture(heartFull_texture);
        UnloadTexture(policeCarTexture);
        UnloadTexture(afterExplosionTexture);
        UnloadTexture(policeCirclesTexture);
        UnloadTexture(smallHeartTexture);


        UnloadSound(sound1);
        UnloadSound(sound2);
        UnloadSound(policeSiren);
        
        UnloadImage(image1);
        UnloadImage(image3);
        UnloadImage(image4);
        UnloadImage(image5);
        UnloadImage(image6);
        UnloadImage(heartEmpty);
        UnloadImage(heartFull);
        UnloadImage(policeCarImage);
        UnloadImage(afterExplosionImage);
        UnloadImage(policeCirclesImg);
        UnloadImage(smallHeartImg);
        
        for(Barrier* barrier : barriersVec){
            delete barrier;
        }
    }

    bool isFinalAnimation(){
        return finalAnimation;
    }

    void restartGame(){
        if(menu.returnRestartGame()){

            canMove = false;
            pageNum = menu.returnChosenCar();
            // finalText.str("");
            crashBool = false;
            catching = false;
            backing = false;
            isAnimationRunning = false;
            policeCarsY = 1000;
            lives = 3;
            score = 0;
            speedOfAnimation = 10;
            finalAnimation = false;
            crashBool = false;
            continueCode = false;
            codeExecuted = false;
            crashOrCheck = std::chrono::system_clock::now();
            lastHeart = std::chrono::system_clock::now(); 
            scoreTime = std::chrono::system_clock::now();
            twoCloseCollisionStart = std::chrono::system_clock::now();
            helicopter1vec2.x = 550;
            helicopter2vec.x = 80;
            helicopter1vec.x = 170;
            police1vec.x = 550;
            police2vec.x = 650;
            helicopter1vec2.y = 1000;
            helicopter2vec.y = 1000;
            helicopter1vec.y = 1000;
            police1vec.y = 1100;
            police2vec.y = 1000;
            jet2vec.y = 700;
            jet1vec.y = 350;
            barriersVec.clear();
            car.setDefaultPos();
            menu.setRestartGame(false);
            rotationSpeedLeft1 = 180.0f;
            rotationSpeedLeft2 = 180.0f;
            rotationSpeedRight1 = 180.0f;
            rotationSpeedPolice1 = 180.0f;
            rotationSpeedPolice2 = 180.0f;
            carRotationLeft1 = 0.0f;
            carRotationLeft2 = 0.0f;
            carRotationRight1 = 0.0f;
            policeRotationRight1 = 0.0f;
            policeRotationRight2 = 0.0f;
        }
        
    }
    
    void displayingAfterExplosion(){
        for(Vector2 pos : afterCollisionPos){
            DrawTexture(afterExplosionTexture, pos.x, pos.y, WHITE);
        }

        for(Barrier* barrier : barriersVec){
            std::vector<int> barrierPos = barrier->getPos();
            if(barrier->returnStatus() == true){
                DrawTexture(afterExplosionTexture, barrierPos[0], barrierPos[1], WHITE);
            }
        }
    }

    void displayHeartOnRoad(){
        if(!finalAnimation){
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastHeart);
            if(duration.count() > 20000){
                lastHeart = std::chrono::system_clock::now();
                luckyNumHeartX = rand() % 450;
                luckyNumHeartX += 200;
                heartY = -10;
                lifeAdded = false;
            }
            
            if(heartY < 1150 && luckyNumHeartX != 0 && !lifeAdded){
                DrawTexture(smallHeartTexture, luckyNumHeartX, heartY, WHITE);
                heartY += speedOfAnimation;
            }
        }
        
        
        
    }

    void afterLivesAnimation(){
        
        if(finalAnimation){
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - majakyTime);
            if(duration.count() < 750){
                DrawTexture(bluredMajakRedTexture, -90, -50, WHITE);
            }
            else if(duration.count() >= 750 && duration.count() <= 1500){
                DrawTexture(bluredMajakBlueTexture, 410, -50, WHITE);
                
            }
            else if(duration.count() > 1500){
                majakyTime = std::chrono::system_clock::now();
            }
            std::ostringstream finalText;
            finalText << "Your final score is " << score << "!";
            std::string finalTextStr = finalText.str();
            DrawText(finalTextStr.c_str(), 150, 100, 50, WHITE);
            
            float getFrameLength = GetFrameTime();
        
            if(posOfTheCarAfterCrash.x + allCars[pageNum].width + 20 < police2vec.x){
                police2vec.x -= 10;
            }
          
            if(posOfTheCarAfterCrash.x + allCars[pageNum].width + 20 > police2vec.x){
                police2vec.x += 9;
            }
            if(police1vec.x < posOfTheCarAfterCrash.x + 50){
                police1vec.x += 10;
            }
            if(police1vec.x > posOfTheCarAfterCrash.x + 50){
                police1vec.x -= 10;
            }


            if(helicopter1vec2.y > car.getPos()[1]){
                if(policeRotationRight1 > finalRotationPolice1){
                    rotationSpeedPolice1 = getFrameLength * finalRotationPolice1;
                    policeRotationRight1 += rotationSpeedPolice1;
                    majakyRotationX += rotationSpeedPolice1;
                    
                    std::cout << "rotace";
                    
                }
            
                DrawTextureEx(texture4, helicopter1vec, carRotationLeft1, 1.0f, WHITE);
                DrawTextureEx(texture3, helicopter2vec, carRotationLeft2, 1.0f, WHITE);
                DrawTextureEx(texture4, helicopter1vec2, carRotationRight1, 1.0f, WHITE);
                DrawTextureEx(policeCarTexture, police1vec, policeRotationRight1, 1.0f, WHITE);
                DrawTextureEx(policeCarTexture, police2vec, policeRotationRight2, 1.0f, WHITE);
                helicopter1vec.y -= 10;
                helicopter2vec.y -= 10;
                helicopter1vec2.y -= 10;
            
            if(police1vec.y > posOfTheCarAfterCrash.y + allCars[pageNum].height + 50){
                police1vec.y -= 10;
            }
            
            else if(police1vec.y < posOfTheCarAfterCrash.y + allCars[pageNum].height + 50){
                police1vec.y += 9;
            }

            if(police2vec.y > posOfTheCarAfterCrash.y + 20){
                police2vec.y -= 10;
            } 
            else if(police2vec.y < posOfTheCarAfterCrash.y + 20){
                police2vec.y += 9;
            }

        } else if(helicopter1vec2.y <= car.getPos()[1]){
            
            if(carRotationLeft1 < finalRotationLeft1){
                rotationSpeedLeft1 = getFrameLength * finalRotationLeft1;
                carRotationLeft1 += rotationSpeedLeft1;
            }
            if(carRotationLeft2 < finalRotationLeft2){
                rotationSpeedLeft2 = getFrameLength * finalRotationLeft2;
                carRotationLeft2 += rotationSpeedLeft2;
            }
            if(carRotationRight1 > finalRotationRight1){
                rotationSpeedRight1 = getFrameLength * finalRotationRight1;
                carRotationRight1 += rotationSpeedRight1;
            }
            if(posOfTheCarAfterCrash.x - 20 > helicopter1vec.x){
                helicopter1vec.x += 10;
            }
            if(posOfTheCarAfterCrash.x - 20 > helicopter2vec.x){
                helicopter2vec.x += 10;
            }
            if(posOfTheCarAfterCrash.x + 20 < helicopter1vec2.x){
                helicopter1vec2.x -= 10;
            }
        
            DrawTextureEx(texture4, helicopter1vec, carRotationLeft1, 1.0f, WHITE);
            DrawTextureEx(texture3, helicopter2vec, carRotationLeft2, 1.0f, WHITE);
            DrawTextureEx(texture4, helicopter1vec2, carRotationRight1, 1.0f, WHITE);
            DrawTextureEx(policeCarTexture, police1vec, policeRotationRight1, 1.0f, WHITE);
            DrawTextureEx(policeCarTexture, police2vec, policeRotationRight2, 1.0f, WHITE);
            } 

            if(jet1vec.y > -400){
                
                DrawTextureEx(texture5, jet1vec, rotation, 1.0f, WHITE);
                DrawTextureEx(texture6, jet2vec, rotation, 1.0f, WHITE);
                
                jet2vec.y -= 14;
                jet1vec.y -= 14;
            }   
        }  
    }

    void updateScore(){
        if(!finalAnimation){
            std::chrono::system_clock::time_point scoreTimeNow = std::chrono::system_clock::now();
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(scoreTimeNow - scoreTime);
            score = (duration.count() / 4); 
        }
        
    }

    void displayScore(){
        std::string score_string = std::to_string(score);
        DrawText(score_string.c_str(), 400, 30, 50, BLACK);
    }

    void displayLives(){
        if(lives == 3){
            
            DrawTexture(heartFull_texture, 750, 10, WHITE);
            DrawTexture(heartFull_texture, 800, 10, WHITE);
            DrawTexture(heartFull_texture, 850, 10, WHITE);
        }
        if(lives == 2){
            
            DrawTexture(heartFull_texture, 750, 10, WHITE);
            DrawTexture(heartFull_texture, 800, 10, WHITE);
            DrawTexture(heartEmpty_texture, 850, 10, WHITE);
        }
        if(lives == 1){
            
            DrawTexture(heartFull_texture, 750, 10, WHITE);
            DrawTexture(heartEmpty_texture, 800, 10, WHITE);
            DrawTexture(heartEmpty_texture, 850, 10, WHITE);
        }
    }

    int getSpeedOfAnimation(){
        return speedOfAnimation;
    }

    void drawCatchingAnimation(){
        if(!finalAnimation){
            if(catching && !backing && policeCarsY > 950){
                DrawTexture(texture4, 80, policeCarsY, WHITE);
                DrawTexture(texture3, 170, policeCarsY, WHITE);
                DrawTexture(texture5, 350, policeCarsY, WHITE);
                DrawTexture(texture4, 550, policeCarsY, WHITE);
                DrawTexture(texture6, 700, policeCarsY, WHITE);
                policeCarsY -= 4;
                if(policeCarsY < 961 && policeCarsY > 940){
                    backing = true;
                    catching = false;
                    catching_end = std::chrono::system_clock::now();  
                }
            }
        
            backing_already = std::chrono::system_clock::now();
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(backing_already - catching_end);

            if(duration.count() < 5000){
                DrawTexture(texture4, 80, policeCarsY, WHITE);
                DrawTexture(texture3, 170, policeCarsY, WHITE);
                DrawTexture(texture5, 350, policeCarsY, WHITE);
                DrawTexture(texture4, 550, policeCarsY, WHITE);
                DrawTexture(texture6, 700, policeCarsY, WHITE);
            }
            
            if(backing && duration.count() > 5000){ 
                DrawTexture(texture4, 80, policeCarsY, WHITE);
                DrawTexture(texture3, 170, policeCarsY, WHITE);
                DrawTexture(texture5, 350, policeCarsY, WHITE);
                DrawTexture(texture4, 550, policeCarsY, WHITE);
                DrawTexture(texture6, 700, policeCarsY, WHITE);
                policeCarsY += 4;
                if(policeCarsY > 1200 && policeCarsY < 1210){
                    backing = false;
                    catching = false;
                }
            }
        }
    }
    void drawOptionsAfterGame(){
        if(finalAnimation){
            std::chrono::milliseconds timeFromDeath = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - restartCount);
            if(timeFromDeath.count() > 4000){
                DrawRectangle(rectMain.x, rectMain.y, rectMain.width, rectMain.height, WHITE);
                DrawRectangle(rectPlayAgain.x, rectPlayAgain.y, rectPlayAgain.width, rectPlayAgain.height, ORANGE);
                DrawRectangle(rectGoMenu.x, rectGoMenu.y, rectGoMenu.width, rectGoMenu.height, ORANGE);
                DrawText("Play again", rectPlayAgain.x + 90, rectPlayAgain.y + 35, 30, WHITE);
                DrawText("Back to menu", rectGoMenu.x + 70, rectGoMenu.y + 35, 30, WHITE);
            }
        }
    }
    
    void roadAnimation(){
        
        int vectorSize = imagesRoadY.size();

        for (int i = 0; i < vectorSize; i++) {
            imagesRoadY[i] += speedOfAnimation;
            

            if (imagesRoadY[i] > 1150 && i == 0) {
                imagesRoadY[0] = imagesRoadY[1] - 2150;

            } else if(imagesRoadY[i] > 1150 && i == 1){
                imagesRoadY[1] = imagesRoadY[0] - 2150;
            }
        }
    }

    void updateSpeedOfBarrier(double num){
        for(Barrier* barrier : barriersVec){
            barrier->updateSpeedOfBarrier(num);
        } 
    }

    
void checkCollision(){ 
        std::chrono::milliseconds codeExecutedDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - codeExecutedRestart);
        std::chrono::milliseconds runningAnimationDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - runningAnimation);
        std::chrono::milliseconds twoCloseCollisionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - twoCloseCollision);

        std::vector<int> carPos = car.getPos();
        std::vector<int> carSize = car.getImageSize();
        int carXPos;
        int carYPos;
        int carWidthF;
        int carHeightF;

        if(pageNum == 0){
            carXPos = carPos[0];
            carYPos = carPos[1]+35;
            carWidthF = allCars[pageNum].width;
            carHeightF = allCars[pageNum].height - 35;
        } else {
            carXPos = carPos[0];
            carYPos = carPos[1];
            carWidthF = allCars[pageNum].width;
            carHeightF = allCars[pageNum].height;
        }
     
        // Rectangle carRect = {(float)carXPos, (float)carYPos, (float)carWidthF, (float)carHeightF};
        Rectangle carRectColl = {(float)carXPos, (float)carYPos+10, (float)carWidthF-10, (float)carHeightF-20};
        Vector2 mainCarCenter = {(float)carXPos + carWidthF / 2, (float)carYPos + carHeightF / 2};
      
        int barrierHeight = 110;
        int barrierWidth = 60;
        Rectangle heartRect = {(float)luckyNumHeartX, (float)heartY, (float)smallHeartTexture.width, (float)smallHeartTexture.height};
        std::chrono::milliseconds lifeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lifeAddedTime);
        if(CheckCollisionRecs(carRectColl, heartRect) && lifeDuration.count() > 5000){
            
            lifeAddedTime = std::chrono::system_clock::now();
            lifeAdded = true;
            if(lives != 3){
                lives++;
                lifeAdded = true;
            }
            
        }
        for (Barrier* barrier : barriersVec) {
            std::vector<int> barrierPos = barrier->getPos();
            std::vector<int> barrierSize = barrier->getImageSize();

            int barrierXPos = barrierPos[0];
            int barrierYPos = barrierPos[1] + 10;
    
            Rectangle barrierRect = {(float)barrierXPos, (float)barrierYPos, 60.0, 90.0};
            Vector2 barrierCenter = {(float)barrierXPos + barrierWidth / 2, (float)barrierYPos + barrierHeight / 2};
            
            if (CheckCollisionRecs(carRectColl, barrierRect)){
                barrier->setStatus(true);
            }
           
            if (CheckCollisionRecs(carRectColl, barrierRect) && twoCloseCollisionDuration.count() > 500 && !finalAnimation) {
                twoCloseCollision = std::chrono::system_clock::now();
                restart = true;
                PlaySound(sound2);
                crashBool = true;
                lives--;
                
                if(lives == 0){

                    majakyTime = std::chrono::system_clock::now();
                    PlaySound(policeSiren);
                    finalAnimation = true;
                    Vector2 posOfTheCar = {(float)car.getPos()[0], (float)car.getPos()[1]};
                    posOfTheCarAfterCrash = posOfTheCar;  
                    restartCount = std::chrono::system_clock::now();
                }
                break;
            } 
            
            if(!barrier->returnStatus() && barrierCenter.x + barrierWidth / 2 < mainCarCenter.x + carWidthF / 2 + barrierWidth / 2 &&
                 barrierCenter.x - barrierWidth / 2 > mainCarCenter.x - carWidthF / 2 - barrierWidth / 2 
                 && std::abs(barrierCenter.y - mainCarCenter.y) > carHeightF / 2 + barrierHeight / 2 + 5 && std::abs(barrierCenter.y - mainCarCenter.y) < carHeightF / 2 + barrierHeight / 2 + 30){
                crashOrCheck = std::chrono::system_clock::now();
                continueCode = true;
            } 
            
            std::chrono::milliseconds crashOrCheckDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - crashOrCheck);
            if(crashOrCheckDuration.count() > 220 && crashOrCheckDuration.count() < 240 && !crashBool && !codeExecuted){
                if(!barrier->returnStatus() && !crashBool && continueCode && isAnimationRunning){
                    lives--;
                    continueCode = false;
                    isAnimationRunning = false;
                    codeExecuted = true;
                    codeExecutedRestart = std::chrono::system_clock::now();
                    if(lives == 0){
                        
                        majakyTime = std::chrono::system_clock::now();
                        PlaySound(policeSiren);
                        finalAnimation = true;
                        Vector2 posOfTheCar = {(float)car.getPos()[0], (float)car.getPos()[1]};
                        posOfTheCarAfterCrash = posOfTheCar;
                        restartCount = std::chrono::system_clock::now();
                    }
                    break;

                }
                if(!barrier->returnStatus() && !crashBool && continueCode && !isAnimationRunning){
                
                    PlaySound(sound1);
                    continueCode = false;
                    isAnimationRunning = true;
                    runningAnimation = std::chrono::system_clock::now();
                    catching = true;
                    backing = false;
                    drawCatchingAnimation();
                    codeExecuted = true;
                    codeExecutedRestart = std::chrono::system_clock::now();
                    break;
                }
            }   
        }
        
        if(codeExecutedDuration.count() > 1000 && codeExecutedDuration.count() < 1050){
            codeExecuted = false; 
        }
        
        if(runningAnimationDuration.count() > 6000 && runningAnimationDuration.count() < 6050){
            isAnimationRunning = false;
        }

        // if(codeExecutedDuration.count() > 4000 && finalAnimation){
        //     drawOptionsAfterGame(); 
        // }
        
        if(twoCloseCollisionDuration.count() > 500 && twoCloseCollisionDuration.count() < 550 && restart){
            crashBool = false;
            restart = false;
        }       
    }   


    void generateBarrier(double num, int howManyTimes){ 
        int repeat = 0;
        int notagain = 0;
        int arrayOfXs[12] = {190, 255, 280, 315, 340, 400, 470, 520, 560, 595, 610, 640};
        int luckyNum = -1;
        while(repeat < howManyTimes){
            luckyNum = rand() % 11;
            
            while(luckyNum == notagain || luckyNum+1 == notagain || luckyNum-1 == notagain || luckyNum+2 == notagain || luckyNum-2 == notagain){
                luckyNum = rand() % 11;
            }
            
            Barrier* barrier = new Barrier(arrayOfXs[luckyNum]);
            barriersVec.push_back(barrier);
            updateSpeedOfBarrier(num);
            repeat++;
            notagain = luckyNum;
        }   
    }

    void deleteBarriers() {
        barriersVec.erase(std::remove_if(barriersVec.begin(), barriersVec.end(), [&](Barrier* barrier) {
            std::vector<int> positions = barrier->getPos();
            if(positions[1] > screenHeight){
                UnloadTexture(barrier->getTexture());
                UnloadImage(barrier->getImage());
                delete barrier;
            }
            return positions[1] > screenHeight;
        }), barriersVec.end());
    }


    void CheckUserInput(){
        int carSpeed = car.getSpeedCar();
        bool moveRight = false;
        bool moveLeft = false;
        bool moveUp = false;
        bool moveDown = false;

        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if(CheckCollisionPointRec(GetMousePosition(), rectGoMenu)){
                StopSound(policeSiren);
                menu.menuSeenSet(true);
                menu.menuStartGameSet(false);
            }
            else if(CheckCollisionPointRec(GetMousePosition(), rectPlayAgain)){
                StopSound(policeSiren);
                menu.menuStartGameSet(true);
                menu.setRestartGame(true);
                restartGame();
            }
        }
    
        if(!finalAnimation && canMove){
            if(IsKeyDown(KEY_W)){
            moveUp = true;
            } 
            if(IsKeyDown(KEY_S)){
                moveDown = true;
            } 
            if(IsKeyDown(KEY_D) && car.getPos()[0] + allCars[pageNum].width < 800){
                moveRight = true;
            } 
            if(IsKeyDown(KEY_A) && car.getPos()[0] > 150){
                moveLeft = true;
            }

            if(IsKeyPressed(KEY_SPACE)){
                pause = !pause;
            }

            int count = 0;
            count += moveRight ? 1 : 0;
            count += moveLeft ? 1 : 0;
            count += moveUp ? 1 : 0;
            count += moveDown ? 1 : 0;
            
            if(count == 1){
                if(IsKeyDown(KEY_W)){
                car.updateCoordinates('y', -carSpeed/2);
                } else if(IsKeyDown(KEY_S)){
                    car.updateCoordinates('y', carSpeed*2);
                } else if(IsKeyDown(KEY_D) && car.getPos()[0] + allCars[pageNum].width < 750){
                    car.updateCoordinates('x', carSpeed*1.5);
                } else if(IsKeyDown(KEY_A) && car.getPos()[0] > 150){
                    car.updateCoordinates('x', -carSpeed*1.5);
                }
            }

            if(count > 1){
                if(moveUp && moveLeft){
                    car.updateCoordinates('y', -carSpeed/2, 'x', -carSpeed*1.5);
                } else if(moveUp && moveRight){
                    car.updateCoordinates('y', -carSpeed/2, 'x', carSpeed*1.5);
                } else if(moveDown && moveRight){
                    car.updateCoordinates('y', carSpeed*2, 'x', carSpeed*1.5);
                } else if(moveDown && moveLeft){
                car.updateCoordinates('y', carSpeed*2, 'x', -carSpeed*1.5); 
                }
            }
        }
    }
        

    std::vector<Barrier*> getBarriers(){
        return barriersVec;
    }

     void update(){
        if(menu.menuStartGame()){
            std::chrono::system_clock::time_point timeToStartGame = std::chrono::system_clock::now();
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeToStartGame - scoreTime);
            handleBeforeGameStarting(duration);
            updateScore();
            car.update();
            
            if(!finalAnimation){
                
                checkCollision();
            }
            CheckUserInput();
        } 
        if(!menu.menuStartGame()){
            scoreTime = std::chrono::system_clock::now(); //Pouzivame scoreTime, protoze to ted k nicemu nepotrebujem
            menu.update();
        }
        restartGame();
            
        
        
    }


    void draw() {
        if(menu.isMenuSeen()){
            menu.draw();
        } else if(!menu.isMenuSeen()) {
            
            DrawTexture(texture1, 0, imagesRoadY[0], WHITE);   
            DrawTexture(texture1, 0, imagesRoadY[1], WHITE);
            displayHeartOnRoad();
            std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - scoreTime);

            if(duration.count() > 3000 && !pause){
                for(Barrier* barrier : barriersVec){
                    barrier->draw();
                    barrier->update();
                }
            }
            displayingAfterExplosion();
            DrawTexture(allCars[pageNum], car.getPos()[0], car.getPos()[1], WHITE);
            if(duration.count() > 3000 && !pause &&!finalAnimation){
                roadAnimation();
                drawCatchingAnimation();  
                displayLives();
                displayScore();
            }

            
            afterLivesAnimation();
            
            drawOptionsAfterGame();
        }   
    }

    void handleBeforeGameStarting(std::chrono::milliseconds duration){
        int fontsizeNum = 100;
        
        if(duration.count() > 0 && duration.count() < 1000){
            DrawText("3", screenWidth/2, screenHeight/2, fontsizeNum, ORANGE);
        } else if(duration.count() > 1000 && duration.count() < 2000){
            DrawText("2", screenWidth/2, screenHeight/2, fontsizeNum, ORANGE);
        } else if(duration.count() > 2000 && duration.count() < 3000){
            DrawText("1", screenWidth/2, screenHeight/2, fontsizeNum, ORANGE);
        } else if(duration.count() > 3000 && duration.count() < 4000){
            canMove = true;
        }
    }
};

int main(){

    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "Cars");
    Game game = Game();
    InitializeBarrierArrays();
    SetTargetFPS(60);
    double updateBarrierSpeed = 0.0;
    
    std::chrono::milliseconds milisecsToAddCar(3000);
    std::chrono::system_clock::time_point holder = std::chrono::system_clock::now();;
    std::chrono::system_clock::time_point time_now;
    std::chrono::microseconds time_now_milisecs;
   
    while(WindowShouldClose() == false){
        time_now = std::chrono::system_clock::now();
        time_now_milisecs = std::chrono::duration_cast<std::chrono::milliseconds>(time_now.time_since_epoch());
        std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - holder);
        BeginDrawing();

        std::vector<Barrier*> barriers = game.getBarriers();

        ClearBackground(RAYWHITE);
        if(game.menu.menuStartGame() && !game.isFinalAnimation()){
            if(duration > milisecsToAddCar && updateBarrierSpeed < 0.5){
            updateBarrierSpeed += 0.1;
            game.generateBarrier(updateBarrierSpeed, 1);
            holder = std::chrono::system_clock::now();
            }
            else if(duration > milisecsToAddCar && updateBarrierSpeed >= 0.5){
                updateBarrierSpeed += 0.2;
                game.generateBarrier(updateBarrierSpeed, 2);
                holder = std::chrono::system_clock::now();
            } else if(duration > milisecsToAddCar && updateBarrierSpeed >= 1){
                updateBarrierSpeed += 0.2;
                game.generateBarrier(updateBarrierSpeed, 3);
                holder = std::chrono::system_clock::now();
            }
        }
        if(game.isFinalAnimation() && !game.menu.isMenuSeen()){
            updateBarrierSpeed = 0.0;
            time_now = std::chrono::system_clock::now();
        }
        game.draw();
        game.update();
        EndDrawing();
    }
    UnloadBarrierArrays();
    CloseWindow();
    return 0;
}