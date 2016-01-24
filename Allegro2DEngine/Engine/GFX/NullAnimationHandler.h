#ifndef A2DE_NULLANIMATIONHANDLER_H
#define A2DE_NULLANIMATIONHANDLER_H

#include "../a2de_vals.h"
#include "ADTAnimationHandler.h"

A2DE_BEGIN

class NullAnimationHandler : public ADTAnimationHandler {
public:

    explicit NullAnimationHandler(Sprite& observed);

    virtual ~NullAnimationHandler() = default;

    virtual bool AddAnimation(const std::string& name) override;

    virtual bool AddAnimation(const std::string& name, const AnimationFrameSet& frames) override;

    virtual bool RemoveAnimation(const std::string& name) override;

protected:
private:
    
};

A2DE_END

#endif // A2DE_NULLANIMATIONHANDLER_H
