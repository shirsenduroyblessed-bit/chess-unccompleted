#include "Scroll.hpp"

AdvancedTable::AdvancedTable(int w = 530, int h = 600, int x = 995, int y = 240, SDL_Window *win = nullptr, SDL_Renderer *render = nullptr)
    : window(win), renderer(render), font(nullptr), titleFont(nullptr), windowWidth(w), windowHeight(h), itemHeight(40), hoveredIndex(-1), selectedIndex(-1), maxScroll(0), targetScroll(0), currentScroll(0), scrollVelocity(0), headerText("Piece's Move Event"), posix(x), posiy(y), download(nullptr), undo_is_true(false), redo_is_true(false)
{ // undo(0), redo(0),
    headerRect = {x, y, w, 70};
    listArea = {x + 20, y + 160, w - 40, h - 230};
}

AdvancedTable::~AdvancedTable()
{
    if (download)
        SDL_DestroyTexture(download);

    for (auto &i : items)
        delete i;

    items.clear();

    for (auto &i : items_remained)
        delete i;

    items_remained.clear();

    buttons.clear();
    if (titleFont)
        TTF_CloseFont(titleFont);
    if (font)
        TTF_CloseFont(font);
}

bool AdvancedTable::init()
{
    font = TTF_OpenFont("font.ttf", 15);
    if (!font)
    {
        font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 12);
        if (!font)
            return true;
    }

    titleFont = TTF_OpenFont("font.ttf", 15);
    if (!titleFont)
    {
        titleFont = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 12);
    }
    // int counter = 1;

    if (!(download = IMG_LoadTexture(renderer, "Pieces/download.png")))
        return true;
    else
        printf("okey\n");

    addButton(headerRect.x + 20, headerRect.y + 90, 140, 60, "UNDO", Colors::RED1, Colors::LIGHT_BLUE, [this]()
              { removeLastItem(); });

    addButton(headerRect.x + 190, headerRect.y + 90, 140, 60, "REDO", Colors::GREEN1, Colors::LIGHT_BLUE, [this]()
              { redoIteam(); });

    addButton(headerRect.x + 380, headerRect.y + 90, 60, 60, download, [this]()
              { down_load(); });

    return false;
}

void AdvancedTable::addItem(std::string text = "123", SDL_Color bg = Colors::WHITE, SDL_Color tc = Colors::BLACK)
{
    auto item = new ListItem(text, bg, tc); // smart pointer no more
    items.push_back(item);
    updateMaxScroll();
}

void AdvancedTable::removeLastItem()
{
    if (!items.empty())
    {
        items_remained.emplace_back(items.back());
        items.pop_back();
        updateMaxScroll();
        if (selectedIndex >= static_cast<int>(items.size()))
        {
            selectedIndex = -1;
        }
        // undo++;
        undo_is_true = true;
    }
}

void AdvancedTable::redoIteam()
{
    if (!items_remained.empty())
    {
        items.emplace_back(items_remained.back());
        items_remained.pop_back();
        updateMaxScroll();
    }
    // undo--;
    // undo = std::max(0, undo);
    redo_is_true = true;
}

void AdvancedTable::make_remainnull()
{
    if (items_remained.empty())
        return;

    for (auto &i : items_remained)
        delete i;
    items_remained.clear();
    // undo = 0;
}

void AdvancedTable::clearItems()
{
    for (auto &i : items)
        delete i;

    items.clear();
    make_remainnull();

    selectedIndex = -1;
    hoveredIndex = -1;
    targetScroll = 0;
    currentScroll = 0;
    scrollVelocity = 0;
    // counter = 0;
    updateMaxScroll();
}

void AdvancedTable::addButton(int x, int y, int w, int h, const std::string &text, SDL_Color normal, SDL_Color hover, std::function<void()> callback)
{
    buttons.emplace_back(x, y, w, h, text, normal, hover, callback);
}

void AdvancedTable::addButton(int x, int y, int w, int h, SDL_Texture *givien, std::function<void()> callback)
{
    buttons.emplace_back(x, y, w, h, givien, callback);
}

void AdvancedTable::updateMaxScroll()
{
    // int totalHeight = ;
    maxScroll = std::max(0, static_cast<int>(items.size() * itemHeight) - listArea.h);
}

void AdvancedTable::smoothScrollTo(float target)
{
    targetScroll = std::max(0.0f, std::min(static_cast<float>(maxScroll), target));
}

void AdvancedTable::updateScrollPhysics()
{
    // Calculate how far we need to move
    float difference = targetScroll - currentScroll;

    // Apply spring-like physics
    // 0.8 = damping (slows down existing velocity)
    // 0.2 = spring strength (how fast to approach target)
    scrollVelocity = scrollVelocity * 0.7f + difference * 0.3f;

    // Update position
    currentScroll += scrollVelocity;

    // Stop when very close (prevents endless tiny movements)
    if (std::abs(difference) < 0.5F)
    {
        currentScroll = targetScroll;
        scrollVelocity = 0;
    }
}

int AdvancedTable::getItemIndexAtPosition(int mouseX, int mouseY)
{
    if (mouseX < listArea.x || mouseX > listArea.x + listArea.w || mouseY < listArea.y || mouseY > listArea.y + listArea.h)
        return -1;

    int relativeY = mouseY - listArea.y + static_cast<int>(currentScroll);
    int index = relativeY / itemHeight;

    if (index >= 0 && index < static_cast<int>(items.size()))
        return index;
    return -1;
}

void AdvancedTable::update()
{
    updateScrollPhysics(); // Smooth scrolling magic!
}

void AdvancedTable::down_load() // --------------download is still in ways
{
    std::cout << "I Love You" << std::endl;
}

