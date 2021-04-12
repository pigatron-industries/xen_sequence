#ifndef ParameterFieldListener_h
#define ParameterFieldListener_h

class ParameterField;

class ParameterFieldListener {
    public:
        ParameterFieldListener() {}
        virtual void onSelectModeChange(ParameterField* field) = 0;
        virtual void onValueChange(ParameterField* field) = 0;
};

#endif