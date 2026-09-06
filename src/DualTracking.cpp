#include "ScriptMgr.h"
#include "SpellMgr.h"
#include "SpellInfo.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "Unit.h"

enum TrackSpells : uint32
{
    SPELL_FIND_HERBS = 2383,
    SPELL_FIND_MINERALS = 2580
};

// World script to modify spell definitions on boot
class mod_dual_tracking_world : public WorldScript
{
public:
    mod_dual_tracking_world() : WorldScript("mod_dual_tracking_world") {}

    void OnStartup() override
    {
        // Mutate "Find Herbs" (2383) to include Mineral tracking as Effect 1
        if (SpellInfo* herbSpell = const_cast<SpellInfo*>(sSpellMgr->GetSpellInfo(SPELL_FIND_HERBS)))
        {
            herbSpell->Effects[EFFECT_1].Effect = SPELL_EFFECT_APPLY_AURA;
            herbSpell->Effects[EFFECT_1].TargetA = TARGET_UNIT_CASTER;
            herbSpell->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_TRACK_RESOURCES;
            herbSpell->Effects[EFFECT_1].MiscValue = 3; // 3 = Minerals
        }

        // Mutate "Find Minerals" (2580) to include Herb tracking as Effect 1
        if (SpellInfo* mineralSpell = const_cast<SpellInfo*>(sSpellMgr->GetSpellInfo(SPELL_FIND_MINERALS)))
        {
            mineralSpell->Effects[EFFECT_1].Effect = SPELL_EFFECT_APPLY_AURA;
            mineralSpell->Effects[EFFECT_1].TargetA = TARGET_UNIT_CASTER;
            mineralSpell->Effects[EFFECT_1].ApplyAuraName = SPELL_AURA_TRACK_RESOURCES;
            mineralSpell->Effects[EFFECT_1].MiscValue = 2; // 2 = Herbs
        }
    }
};

// Unit script to enforce profession requirements when the aura is applied
class mod_dual_tracking_unit : public UnitScript
{
public:
    mod_dual_tracking_unit() : UnitScript("mod_dual_tracking_unit") {}

    void OnAuraApply(Unit* unit, Aura* aura) override
    {
        if (!unit || !unit->IsPlayer() || !aura)
            return;

        Player* player = unit->ToPlayer();
        uint32 spellId = aura->GetId();

        // If using Find Herbs without Mining, zero out the secondary Mineral tracking effect
        if (spellId == SPELL_FIND_HERBS && !player->HasSkill(SKILL_MINING))
        {
            if (AuraEffect* eff = aura->GetEffect(EFFECT_1))
                eff->SetAmount(0);
        }
        // If using Find Minerals without Herbalism, zero out the secondary Herb tracking effect
        else if (spellId == SPELL_FIND_MINERALS && !player->HasSkill(SKILL_HERBALISM))
        {
            if (AuraEffect* eff = aura->GetEffect(EFFECT_1))
                eff->SetAmount(0);
        }
    }
};

void Addmod_dual_trackingScripts()
{
    new mod_dual_tracking_world();
    new mod_dual_tracking_unit();
}
