#pragma once
class SceneScript
{
public:
    virtual ~SceneScript() {}
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};
