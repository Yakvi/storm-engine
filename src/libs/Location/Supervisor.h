// ============================================================================================
// Spirenkov Maxim aka Sp-Max Shaman, 2001
// --------------------------------------------------------------------------------------------
// Sea Dogs II
// --------------------------------------------------------------------------------------------
// Supervisor
// --------------------------------------------------------------------------------------------
// Object controlling the movement of characters
// ============================================================================================

#pragma once

class Character;
class LocatorArray;
struct CVECTOR;

#define MAX_CHARACTERS 64

class Supervisor
{
    friend Character;

  public:
    struct CharacterInfo
    {
        Character *c; // The character we interact with
        float d;      // Character distance
        float maxD;   // The largest analyzed distance
    };

    struct FindCharacter
    {
        Character *c;     // The character we were looking for
        float dx, dy, dz; // Vector from the character to us
        float d2;         // The square of the distance to the character in xz
        float l, r, n;    // Distance to clipping planes (optional)
        float sectDist;   // Distance to the sector
    };

    struct CharacterEx
    {
        Character *c;
        float lastTime;
    };

    // --------------------------------------------------------------------------------------------
    // Construction, destruction
    // --------------------------------------------------------------------------------------------
  public:
    Supervisor();
    virtual ~Supervisor();

    // Check for free position
    bool CheckPosition(float x, float y, float z, Character *c) const;
    // Find characters by radius
    bool FindCharacters(FindCharacter fndCharacter[MAX_CHARACTERS], long &numFndCharacters, Character *chr,
                        float radius, float angTest = 0.0f, float nearPlane = 0.4f, float ax = 0.0f,
                        bool isSort = false, bool lookCenter = false) const;

    void Update(float dltTime);
    void PreUpdate(float dltTime) const;
    void PostUpdate(float dltTime);

    // Set loading positions
    void SetSavePositions() const;
    // Delete positions for loading
    void DelSavePositions(bool isTeleport) const;

    // Find the best locator to continue walking the character
    long FindForvardLocator(LocatorArray *la, const CVECTOR &pos, const CVECTOR &norm, bool lookChr = false) const;

    // --------------------------------------------------------------------------------------------
    // Encapsulation
    // --------------------------------------------------------------------------------------------
  private:
    // Add character to location
    void AddCharacter(Character *ch);
    // Remove character from location
    void DelCharacter(Character *ch);

    float time, waveTime;
    long curUpdate;

  public:
    CharacterEx character[MAX_CHARACTERS];
    long numCharacters;
    CharacterInfo colchr[MAX_CHARACTERS * MAX_CHARACTERS];
    long numColChr;
    bool isDelete;
    Character *player;
};

