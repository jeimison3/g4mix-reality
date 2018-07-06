class SDApp {
    private:
        bool    Running;
    public:
        SDApp();
        int OnExecute();
    public:
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
};
