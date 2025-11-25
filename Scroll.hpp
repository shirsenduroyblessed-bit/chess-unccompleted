#include "All.hpp"

struct ListItem
{
    std::string text;
    SDL_Color bgColor;
    SDL_Color textColor;
    std::function<void()> onClick;

    ListItem(const std::string &t, SDL_Color bg = Colors::WHITE, SDL_Color tc = Colors::BLACK) : text(t), bgColor(bg), textColor(tc), onClick(nullptr) {}
    ~ListItem() { std::cout << "BYE" << std::endl; }
};

struct Button
{
    SDL_Rect rect;
    std::string text;
    SDL_Color normalColor;
    SDL_Color hoverColor;
    std::function<void()> onClick;
    SDL_Texture *icon = nullptr;
    bool isHovered;
    // bool if_textured_based;

    Button(int x, int y, int w, int h, const std::string &t,
           SDL_Color normal, SDL_Color hover, std::function<void()> callback)
        : rect{x, y, w, h}, text(t), normalColor(normal),
          hoverColor(hover), onClick(callback), isHovered(false) {}

    Button(int x, int y, int w, int h, SDL_Texture *temp, std::function<void()> callback) : rect{x, y, w, h}, icon(temp), onClick(callback) {}

    bool contains(int x, int y) const
    {
        return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
    }
};

class AdvancedTable
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font, *titleFont;
    // bool running;

    SDL_Rect listArea;

    std::vector<ListItem *> items;          // smart pointer no more
    std::vector<ListItem *> items_remained; // pointer no more
    std::vector<Button> buttons;
    // std::function<void()> lamda;

    std::string headerText;
    SDL_Rect headerRect;
    SDL_Texture *download;

    int itemHeight, hoveredIndex, selectedIndex;
    // int counter;
    int windowWidth, windowHeight;
    int posix, posiy;
    int maxScroll;
    float targetScroll;
    float currentScroll;
    float scrollVelocity;
    bool undo_is_true, redo_is_true;

    AdvancedTable(int, int, int, int, SDL_Window *, SDL_Renderer *);
    ~AdvancedTable();

    int getItemIndexAtPosition(int, int);

    bool init();

    void render();

    void addItem(std::string, SDL_Color, SDL_Color);
    void removeLastItem();
    void make_remainnull();
    void redoIteam();
    void clearItems();
    void updateMaxScroll();
    void smoothScrollTo(float);
    void updateScrollPhysics();
    void update();
    void renderButton(const Button &);
    void renderList();
    void renderScrollbar();
    void renderHeader();
    void renderText(const std::string &, int, int, SDL_Color, TTF_Font *);

    void renderTextCentered(const std::string &, const SDL_Rect &, SDL_Color, TTF_Font *);
    void addButton(int, int, int, int, const std::string &, SDL_Color, SDL_Color, std::function<void()>);
    void down_load();
    void addButton(int, int, int, int, SDL_Texture *, std::function<void()>);
};

class event
{
public:
    int pre_r, pre_c, n_r, n_c, castled;
    std::string what_event;
    PIECES selectd, targtd;

    event(int i1, int i2, int i3, int i4, int j1, PIECES selct, PIECES targt, std::string str_) : pre_r(i1), pre_c(i2), n_r(i3), n_c(i4), castled(j1), selectd(selct), targtd(targt), what_event(str_) {}

    std::string given_str()
    {
        return what_event;
    }
    ~event()
    {
        std::cout << "Deleted" << std::endl;
    }
};

