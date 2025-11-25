#include "player.hpp"

bool WindoW::init()
{
    if (SDL_Init(SDL_INIT_VIDEO))
        return true;

    if (IMG_Init(IMG_Flag) == 0)
        return true;

    if (Mix_Init(MIXER_FLAGS) == 0)
        return true;

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048))
        return true;

    if (TTF_Init())
        return true;

    if (!(window = SDL_CreateWindow("SYMETTRIC_IRON_CHESS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN)))
        return true;

    if (!(render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
        return true;

    if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND)))
        return true;

    SDL_SetCursor(cursor);

    img = IMG_LoadTexture(render, "pic/ChessNeo.png");
    clk = Mix_LoadMUS("Sound/click.mp3");

    Button *btn1 = new Button(460, 100, 250, 60, "Play NEW", Colors::neoBlue, Colors::neoRed, [this]()
                              { is_new = true;Mix_PlayMusic(clk,0); SDL_Delay(1000); });

    Button *btn2 = new Button(460, 200, 250, 60, "Play Continue", Colors::neogreen, Colors::neoRed, [this]()
                              { Mix_PlayMusic(clk, 0); is_continue = true; SDL_Delay(1000); });

    Button *btn3 = new Button(460, 300, 250, 60, "EXIT", {60, 50, 70, 100}, Colors::neoRed, [this]()
                              { is_exit = true;Mix_PlayMusic(clk,0);SDL_Delay(1000); });

    buttons.emplace_back(btn1);
    buttons.emplace_back(btn2);
    buttons.emplace_back(btn3);
    return false;
}

void WindoW::handleEvent()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            is_exit = true;
            break;
        case SDL_MOUSEMOTION:
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            // Update button hover states
            for (auto &btn : buttons)
                btn->isHovered = btn->contains(mouseX, mouseY);
        }
        break;

        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Check buttons
            for (auto &btn : buttons)
                if (btn->contains(mouseX, mouseY) && btn->onClick)
                {
                    btn->onClick();
                    clicked = true;
                }
        }
        break;
        }
    }
}

void WindoW::run()
{
    while (running)
    {
        handleEvent();
        if (clicked)
        {
            clicked = false;
            if (is_new)
            {
                running = false;
                *ptr = 1;
                break;
            }
            if (is_exit)
            {
                running = false;
                *ptr = 2;
                break;
            }
            if (is_continue)
            {
                running = false;
                *ptr = 3;
                break;
            }
        }
        rener();
        SDL_RenderPresent(render);
        SDL_Delay(16);
    }
}

void WindoW::rener()
{
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, nullptr);

    SDL_Rect temp = {0, 0, 500, 500};
    SDL_RenderCopy(render, img, nullptr, &temp);

    for (const auto &btn : buttons)
    {
        SDL_Color color = btn->isHovered ? btn->hoverColor : btn->normalColor;

        SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(render, &btn->rect);

        SDL_SetRenderDrawColor(render, Colors::DARK_GRAY.r, Colors::DARK_GRAY.g,
                               Colors::DARK_GRAY.b, Colors::DARK_GRAY.a);
        SDL_RenderDrawRect(render, &btn->rect);

        // renderTextCentered(btn.text, btn.rect, Colors::BLUE, nullptr);

        {
            TTF_Font *useFont = TTF_OpenFont("Font/Bold.ttf", 40);
            SDL_Surface *surface = TTF_RenderText_Blended(useFont, btn->text.c_str(), Colors::BLACK);

            SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);

            int textX = btn->rect.x + (btn->rect.w - surface->w) / 2;
            int textY = btn->rect.y + (btn->rect.h - surface->h) / 2;

            SDL_Rect destRect = {textX, textY, surface->w, surface->h};
            SDL_RenderCopy(render, texture, nullptr, &destRect);

            TTF_CloseFont(useFont);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    }
}
