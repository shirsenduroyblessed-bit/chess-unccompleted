#include "Scroll.hpp"

void AdvancedTable::renderButton(const Button &btn)
{
    if (!btn.icon)
    {
        SDL_Color color = btn.isHovered ? btn.hoverColor : btn.normalColor;

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &btn.rect);

        SDL_SetRenderDrawColor(renderer,
                               Colors::DARK_GRAY.r, Colors::DARK_GRAY.g,
                               Colors::DARK_GRAY.b, Colors::DARK_GRAY.a);
        SDL_RenderDrawRect(renderer, &btn.rect);

        renderTextCentered(btn.text, btn.rect, Colors::BLUE, nullptr);
    }
    else
    {
        SDL_RenderCopy(renderer, btn.icon, nullptr, &btn.rect);
    }
}

void AdvancedTable::renderList()
{
    SDL_RenderSetClipRect(renderer, &listArea);

    int scrollInt = static_cast<int>(currentScroll); // Convert float to int
    int firstVisible = scrollInt / itemHeight;
    int lastVisible = (scrollInt + listArea.h) / itemHeight + 2;

    firstVisible = std::max(0, firstVisible);
    lastVisible = std::min(static_cast<int>(items.size()), lastVisible);

    for (int i = firstVisible; i < lastVisible; i++)
    {
        int yPos = listArea.y + (i * itemHeight) - scrollInt;

        SDL_Rect itemRect = {
            listArea.x,
            yPos,
            listArea.w,
            itemHeight - 2};

        // Determine background color
        SDL_Color bgColor = items[i]->bgColor;
        if (i == selectedIndex)
            bgColor = Colors::GREEN;
        else if (i == hoveredIndex)
            bgColor = Colors::LIGHT_GRAY;

        // Draw item
        SDL_SetRenderDrawColor(renderer,
                               bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &itemRect);

        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderDrawRect(renderer, &itemRect);

        // Render text
        renderText(items[i]->text, itemRect.x + 10, itemRect.y + (itemHeight - 30) / 2, items[i]->textColor, nullptr);
    }

    SDL_RenderSetClipRect(renderer, nullptr);
}

void AdvancedTable::renderScrollbar()
{
    if (maxScroll <= 0)
        return;

    int barX = listArea.x + listArea.w + 5;
    int barY = listArea.y;
    int barWidth = 8;
    int barHeight = listArea.h;

    SDL_Rect track = {barX, barY, barWidth, barHeight};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &track);

    float visibleRatio = static_cast<float>(listArea.h) / (items.size() * itemHeight);
    int thumbHeight = std::max(20, static_cast<int>(barHeight * visibleRatio));

    float scrollPercentage = currentScroll / maxScroll;
    int thumbY = barY + static_cast<int>((barHeight - thumbHeight) * scrollPercentage);

    SDL_Rect thumb = {barX, thumbY, barWidth, thumbHeight};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &thumb);
}

void AdvancedTable::renderHeader()
{
    SDL_SetRenderDrawColor(renderer, Colors::BLUE.r, Colors::BLUE.g, Colors::BLUE.b, Colors::BLUE.a);
    SDL_RenderFillRect(renderer, &headerRect);

    if (!headerText.empty() && titleFont)
    {
        renderTextCentered(headerText, headerRect, Colors::WHITE, titleFont);
    }
}

void AdvancedTable::renderText(const std::string &text, int x, int y, SDL_Color color, TTF_Font *customFont = nullptr)
{
    TTF_Font *useFont = customFont ? customFont : font;
    SDL_Surface *surface = TTF_RenderText_Blended(useFont, text.c_str(), color);
    if (!surface)
        return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void AdvancedTable::renderTextCentered(const std::string &text, const SDL_Rect &rect, SDL_Color color, TTF_Font *customFont)
{
    TTF_Font *useFont = customFont ? customFont : font;
    SDL_Surface *surface = TTF_RenderText_Blended(useFont, text.c_str(), color);
    if (!surface)
        return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textX = rect.x + (rect.w - surface->w) / 2;
    int textY = rect.y + (rect.h - surface->h) / 2;

    SDL_Rect destRect = {textX, textY, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void AdvancedTable::render()
{
    // SDL_SetRenderDrawColor(renderer, 220, 220, 225, 255);
    // SDL_RenderClear(renderer);

    renderHeader();

    // Render buttons
    for (const auto &btn : buttons)
        renderButton(btn);

    // List background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &listArea);

    renderList();
    renderScrollbar();

    // Status
    std::string status = "Items: " + std::to_string(items.size()) + " | Selected: " + (selectedIndex >= 0 ? std::to_string(selectedIndex + 1) : "None");
    renderText(status, 20 + posix, windowHeight - 35 + posiy, Colors::BLACK, nullptr);

    // SDL_RenderPresent(renderer);
}
