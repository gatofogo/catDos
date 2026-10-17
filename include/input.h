#ifndef Input_h
#define Input_h
class Input{
public:
    virtual bool has_key() = 0;
    virtual int get_key() = 0;
    virtual ~Input() = default;
};
class WinInput : public Input{
public:
    bool has_key() override;
    int get_key() override;
};
#endif