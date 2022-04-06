#ifndef __CONTEXTGLOBAL_HPP__
#define __CONTEXTGLOBAL_HPP__

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "enum_sol.hpp"
//  #include "CaseMap.hpp"

using namespace std;
using namespace sf;

class CaseMap;
// static float CaseMap::getScaleCaseMap();

class ContextGlobal
{

private:
    Vector2u _dimensionFenetre;
    float _ratioFenetre;
    RenderWindow _window;
    float _tailleReference;
    bool _eventPresent;
    Event _event;
    bool _isRun;

    // Static
private:
    static ContextGlobal _singleton;

public:
    static ContextGlobal &getInstance();

public:
    ~ContextGlobal();

    void init(const Vector2u &dimFenetre);
    void dessinerFenetre(const Drawable &obj);
    void dessinerFenetre(const Drawable *obj);
    void afficherFenetre();
    void update();

    // Getter
    const RenderWindow &getWindow() const;
    const Vector2u &getDimensionFenetre() const;
    uint getLargeurFenetre() const;
    uint getHauteurFenetre() const;
    bool getIsRun() const;
    bool getPollEvent();
    const Event &getEvent() const;
    Event::EventType getEventType() const;
    const float getTailleReference() const;

    // Setter
    void setIsRun(bool run);
    void setTailleReference(float caseMap);

private:
    ContextGlobal();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/
inline const RenderWindow &ContextGlobal::getWindow() const { return _window; }

inline const Vector2u &ContextGlobal::getDimensionFenetre() const { return _dimensionFenetre; }
inline uint ContextGlobal::getLargeurFenetre() const { return _dimensionFenetre.x; }
inline uint ContextGlobal::getHauteurFenetre() const { return _dimensionFenetre.y; }

inline bool ContextGlobal::getIsRun() const { return _isRun; }

inline bool ContextGlobal::getPollEvent()
{
    // Récupération dans la queue des events
    _eventPresent = _window.pollEvent(_event);
    update(); // Update le context
    return _eventPresent;
}
inline const Event &ContextGlobal::getEvent() const { return _event; }
inline Event::EventType ContextGlobal::getEventType() const { return _event.type; }

inline const float ContextGlobal::getTailleReference() const { return _tailleReference; }

// Setter
inline void ContextGlobal::setIsRun(bool run) { _isRun = run; }
inline void ContextGlobal::setTailleReference(float scaleCaseMap) { _tailleReference = scaleCaseMap; }

#endif