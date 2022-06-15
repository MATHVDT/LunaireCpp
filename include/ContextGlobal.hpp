#ifndef __CONTEXT_GLOBAL_HPP__
#define __CONTEXT_GLOBAL_HPP__

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "EnumTypeSol.hpp"
#include "EnumTypeStructure.hpp"
#include "EnumTypeRessource.hpp"

#include "Carte.hpp"

using namespace std;
using namespace sf;

class Carte;
class CaseMap;

class ContextGlobal
{

private:
    Vector2u _dimensionFenetre;
    float _ratioFenetre;
    RenderWindow _window;
    float _tailleReference;
    float _scaleReference;
    bool _eventPresent;
    Event _event;
    bool _isRun;

    Carte *_carte;
    CaseMap *_caseOver;
    CaseMap *_caseSelectionnee;

    TYPE_STRUCTURE _editionStructureSelectionnee;

private: // Static
    static ContextGlobal *_singleton;

public: // Static
    static ContextGlobal *getInstance();

public:
    ~ContextGlobal();

    void init(const Vector2u &dimFenetre);
    void dessinerFenetre(const Drawable &obj);
    void dessinerFenetre(const Drawable *obj);
    void afficherFenetre();
    void update();
    void calculCaseOver();
    void checkClavierStructures();
    void clickSouris();

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
    const float getScaleReference() const;
    CaseMap *getCaseOver() const;
    CaseMap *getCaseSelectionnee() const;
    TYPE_STRUCTURE getEditionStructureSelectionnee() const;

    // Setter
    void setIsRun(bool run);
    void setTailleReference(float tailleCaseMap);
    void setScaleReference(float scaleCaseMap);
    void setCarte(Carte *carte);
    void setCaseOver(CaseMap *caseOver);
    void setCaseSelectionnee(bool reset = false);
    void setEditionStructureSelectionnee(TYPE_STRUCTURE structSelect);

private:
    ContextGlobal();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

// Getter
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
inline const float ContextGlobal::getScaleReference() const { return _scaleReference; }

inline CaseMap *ContextGlobal::getCaseOver() const { return _caseOver; }
inline CaseMap *ContextGlobal::getCaseSelectionnee() const { return _caseSelectionnee; }
inline TYPE_STRUCTURE ContextGlobal::getEditionStructureSelectionnee() const { return _editionStructureSelectionnee; }

// Setter
inline void ContextGlobal::setIsRun(bool run) { _isRun = run; }
inline void ContextGlobal::setTailleReference(float tailleCaseMap) { _tailleReference = tailleCaseMap; }
inline void ContextGlobal::setScaleReference(float scaleCaseMap) { _scaleReference = scaleCaseMap; }
inline void ContextGlobal::setCaseOver(CaseMap *caseOver) { _caseOver = caseOver; }
inline void ContextGlobal::setEditionStructureSelectionnee(TYPE_STRUCTURE structSelect) { _editionStructureSelectionnee = structSelect; }

#endif