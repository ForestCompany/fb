int menu(SDL_Renderer* renderer) {
    Entity* background = CreateEntity(renderer, 0, 0, SCREENWIDTH, SCREENHEIGHT, "images/backgroundMenu.png");
    Button* startButton = CreateButton(renderer, (SDL_Rect){BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT}, "images/startButton.png","images/startButton2.png");
    Button* settingsButton = CreateButton(renderer, (SDL_Rect){BUTTON_X, BUTTON_Y + BUTTON_HEIGHT + BUTTON_Y_PADDING_PERCENTAGE, BUTTON_WIDTH, BUTTON_HEIGHT}, "images/settingsButton.png","images/settingsButton2.png");
    Button* quitButton = CreateButton(renderer, (SDL_Rect){BUTTON_X, BUTTON_Y + 2 * (BUTTON_HEIGHT + BUTTON_Y_PADDING_PERCENTAGE), BUTTON_WIDTH, BUTTON_HEIGHT}, "images/quitButton.png","images/quitButton2.png");
    
    char *buttonArray[3] = {startButton, settingsButton, quitButton};
    int selectedButtonIndex = -1; // Індекс обраної кнопки, початково встановлений на -1 (ні одна кнопка не була обрана)

    int mousecordsX = 0;
    int mousecordsY = 0;
    SDL_Event event;
    bool isexit = false;
    while (!isexit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isexit = true;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mousecordsX, &mousecordsY);
                    for (int i = 0; i < 3; i++) { // Перевіряємо кожну кнопку
                        if (CheckButton(&(SDL_Point){mousecordsX, mousecordsY}, &(buttonArray[i]->rect))) {
                            selectedButtonIndex = i; // Запам'ятовуємо індекс натиснутої кнопки
                            isexit = true; // Виходимо з циклу, оскільки кнопка була обрана
                            break;
                        }
                    }
                    break;
            }
        }
        ShowEntity(renderer, background);
        ShowButton(renderer, quitButton);
        ShowButton(renderer, settingsButton);
        ShowButton(renderer, startButton);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000. / fps);
    }
    SDL_RenderPresent(renderer);
    DestroyEntity(background);
  
    return selectedButtonIndex; // Повертаємо індекс обраної кнопки
}