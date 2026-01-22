#pragma region Information

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTitleChangedSignature, FString, NewTitle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDescriptionChangedSignature, FString, NewDescription);

USTRUCT(BlueprintType)
struct FInformationData
{
GENERATED_BODY()

protected:
// Title of the information
UPROPERTY(EditAnywhere, BlueprintReadWrite)
FString Title;

// Description of the information
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
FString Description;

public:
// Delegate for title is changed event
FOnTitleChangedSignature OnTitleChanged;

// Delegate for description is changed event	
FOnDescriptionChangedSignature OnDescriptionChanged;

public:
// Constructor 
FInformationData()
: Title("Default Title")
, Description("Default Description")
{}

// Equality operators
bool operator!=(const FInformationData& Other) const
{
return !(*this == Other);
}

// Equality operators
bool operator==(const FInformationData& Other) const
{
return
Title == Other.Title &&
Description == Other.Description;
}

// Getters and Setters
FString& GetTitle()  
{
return Title; 
}

// Getters and Setters
FString& GetDescription()  
{
return Description;
}

// Setters with event broadcasting
void SetTitle(const FString& NewTitle) 
{
Title = NewTitle;
OnTitleChanged.Broadcast(NewTitle);
}

// Setters with event broadcasting
void SetDescription(const FString& NewDescription)
{
Description = NewDescription; 
OnDescriptionChanged.Broadcast(NewDescription);
}
};

#pragma endregion

#pragma region Attribute

UENUM(BlueprintType)
enum class ECharacterAttributeType : uint8
{
Null			UMETA(DisplayName = "Select Attribute Type"),
Health			UMETA(DisplayName = "Health"),
Stamina			UMETA(DisplayName = "Stamina"),
Energy			UMETA(DisplayName = "Energy"),
Shield			UMETA(DisplayName = "Shield"),
Output			UMETA(DisplayName = "Output"),
Actuation		UMETA(DisplayName = "Actuation"),
Integrity		UMETA(DisplayName = "Integrity"),
Capacity		UMETA(DisplayName = "Capacity"),
Regeneration	UMETA(DisplayName = "Regeneration"),
Max				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EPrimaryAttributeType : uint8
{
Null	UMETA(DisplayName = "Select Primary Attribute"),
Health	UMETA(DisplayName = "Health"),
Stamina UMETA(DisplayName = "Stamina"),
Energy	UMETA(DisplayName = "Energy"),
Shield	UMETA(DisplayName = "Shield"),
Max		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ESecondaryAttributeType : uint8
{
Null			UMETA(DisplayName = "Select Upgradeable Attribute"),
Output			UMETA(DisplayName = "Output"),
Actuation		UMETA(DisplayName = "Actuation"),
Integrity		UMETA(DisplayName = "Integrity"),
Capacity		UMETA(DisplayName = "Capacity"),
Regeneration	UMETA(DisplayName = "Regeneration")
};

USTRUCT(BlueprintType)
struct FAttributeModule
{
GENERATED_BODY()

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float MinimumValue;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float MaximumValue;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float CurrentValue;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
bool bEnableUpdate = true;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float RegenerateValue = 1.f; // Default regeneration value

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float DepleteValue = 1.f;    // Default depletion value


public:
// Constructor 
FAttributeModule()
: MinimumValue(0.f)
, MaximumValue(100.f)
, CurrentValue(100.f)
{}

// Equality operators
bool operator!=(const FAttributeModule& Other) const
{
return !(*this == Other);
}

// Equality operators
bool operator==(const FAttributeModule& Other) const
{
return
MinimumValue == Other.MinimumValue &&
MaximumValue == Other.MaximumValue &&
CurrentValue == Other.CurrentValue &&
bEnableUpdate == Other.bEnableUpdate && 
RegenerateValue == Other.RegenerateValue;
}

float GetMinimumValue() const { return MinimumValue; }
float GetMaximumValue() const { return MaximumValue; }
float GetCurrentValue() const { return CurrentValue; }
bool IsUpdateEnabled() const  { return bEnableUpdate; }
float GetRegenerateValue() const { return RegenerateValue; }
float GetDepleteValue() const { return DepleteValue; }

// X: Minimum, Y: Maximum, Z: Current
FVector GetAttributeValues() const 
{ 
return FVector(MinimumValue, MaximumValue, CurrentValue); 
}

// Set X: Minimum, Y: Maximum, Z: Current
void SetValue(float InMinValue, float InMaxValue, float InCurrentValue) 
{ 
MinimumValue = InMinValue;
MaximumValue = InMaxValue;
CurrentValue = InCurrentValue;
}

// Set Update Enabled
void SetUpdateEnabled(bool bInEnableUpdate) { bEnableUpdate = bInEnableUpdate; }
void SetRegenerateValue(float InRegenerateValue) { RegenerateValue = InRegenerateValue; }
void SetDepleteValue(float InDepleteValue) { DepleteValue = InDepleteValue; }
};

USTRUCT(BlueprintType)
struct FCharacterAttribute
{
GENERATED_BODY()

protected:
// Primary Attributes
UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Health;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Stamina;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Energy;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Shield;

//Passive Attributes
UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Output; // Damage + protection

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Actuation;    // Movement speed + jump height

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Integrity;    // Health + shield

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Capacity;     // Energy pool + efficiency

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FAttributeModule Regeneration; // Shield recharge + cooldowns

// Available Upgrade Points
UPROPERTY(EditAnywhere, BlueprintReadWrite)
int32 UpgradePoint; // Default to 0

public:
FCharacterAttribute()
: Health()
, Stamina()
, Energy()
, Shield()
, Output()
, Actuation()
, Integrity()
, Capacity()
, Regeneration()
, UpgradePoint(0)
{
Health.SetValue(0.0f, 100.0f, 100.0f);
Stamina.SetValue(0.0f, 50.0f, 50.0f);
Energy.SetValue(0.0f, 50.0f, 50.0f);
Shield.SetValue(0.0f, 25.0f, 25.0f);
Output.SetValue(10.0f, 100.0f, 10.0f);
Actuation.SetValue(15.0f, 50.0f, 15.0f);
Integrity.SetValue(20.0f, 80.0f, 20.0f);
Capacity.SetValue(10.0f, 50.0f, 10.0f);
Regeneration.SetValue(2.0f, 20.0f, 2.0f);
}

FAttributeModule& GetHealthAttributeModule()		{ return Health; }
FAttributeModule& GetStaminaAttributeModule()		{ return Stamina; }
FAttributeModule& GetEnergyAttributeModule()		{ return Energy; }
FAttributeModule& GetShieldAttributeModule()		{ return Shield; }
FAttributeModule& GetOutputAttributeModule()		{ return Output; }
FAttributeModule& GetActuationAttributeModule()		{ return Actuation; }
FAttributeModule& GetIntegrityAttributeModule()		{ return Integrity; }
FAttributeModule& GetCapacityAttributeModule()		{ return Capacity; }
FAttributeModule& GetRegenerationAttributeModule()	{ return Regeneration; }

FAttributeModule& GetPrimaryAttributeModuleByType(EPrimaryAttributeType Type)
{
switch (Type)
{
case EPrimaryAttributeType::Health:
return Health;
case EPrimaryAttributeType::Stamina:
return Stamina;
case EPrimaryAttributeType::Energy:
return Energy;
case EPrimaryAttributeType::Shield:
return Shield;
default:
#if WITH_EDITOR
UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeModuleByType: Invalid Primary Attribute Type selected."));
#endif
checkNoEntry(); 
return *(new FAttributeModule());
}
}
FAttributeModule& GetSecondaryAttributeModuleByType(ESecondaryAttributeType Type)
{
switch (Type)
{
case ESecondaryAttributeType::Output:
return Output;
case ESecondaryAttributeType::Actuation:
return Actuation;
case ESecondaryAttributeType::Integrity:
return Integrity;
case ESecondaryAttributeType::Capacity:
return Capacity;
case ESecondaryAttributeType::Regeneration:
return Regeneration;
default:
#if WITH_EDITOR
UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeModuleByType: Invalid Secondary Attribute Type selected."));
#endif
checkNoEntry();
return *(new FAttributeModule());
}
}
};

#pragma endregion

#pragma region Ability

UENUM(BlueprintType)
enum class ECharacterAbilityType : uint8
{
Null UMETA(DisplayName = "Select Character Ability"),
CombatStrike UMETA(DisplayName = "Combat Strike"),
LaserPulse UMETA(DisplayName = "Laser Pulse"),
PlasmaShield UMETA(DisplayName = "Plasma Shield"),
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
Null		UMETA(DisplayName = "Select Ability Type"),
Passive		UMETA(DisplayName = "Passive"),
Active		UMETA(DisplayName = "Active"),
Ultimate	UMETA(DisplayName = "Ultimate"),
Max			UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAbilityEffectType : uint8
{
Null	UMETA(DisplayName = "Select Ability Effect Type"),
Damage	UMETA(DisplayName = "Damage"),
Defense UMETA(DisplayName = "Defense"),
Heal	UMETA(DisplayName = "Heal"),
Buff	UMETA(DisplayName = "Buff"),
Debuff	UMETA(DisplayName = "Debuff"),
Spawn	UMETA(DisplayName = "Spawn"),
Custom	UMETA(DisplayName = "Custom"),
Max		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAbilityCostType : uint8
{
Null		UMETA(DisplayName = "Select Ability Cost Type"),
Health		UMETA(DisplayName = "Health"),
Stamina		UMETA(DisplayName = "Stamina"),
Energy		UMETA(DisplayName = "Energy"),
Shield		UMETA(DisplayName = "Shield"),
Max			UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FAbilityModule
{
GENERATED_BODY()

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
FString Title;
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
FString Description;
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
EAbilityType AbilityType;
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
EAbilityEffectType EffectType;
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
EAbilityCostType CostType;
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
float Output;
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float Magnitude;
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float Multiplier;
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float Duration;
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float CooldownTime;
UPROPERTY(EditAnywhere, BlueprintReadWrite)	
float Cost;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
TSubclassOf<UAnimMontage> AbilityMontage;

public:
// Constructor
FAbilityModule()
: Title("DefaultAbility")
, Description("DefaultAbilityDescription")
, AbilityType(EAbilityType::Passive)
, EffectType(EAbilityEffectType::Damage)
, CostType(EAbilityCostType::Health)
, Output(0.f)
, Magnitude(0.f)
, Multiplier(1.f)
, Duration(0.f)
, CooldownTime(0.f)
, Cost(0.f)
, AbilityMontage(nullptr)
{}

// Inequality operators
bool operator!=(const FAbilityModule& Other) const
{
return !(*this == Other);
}

// Equality operators
bool operator==(const FAbilityModule& Other) const
{
return
Title == Other.Title &&
Description == Other.Description &&
AbilityType == Other.AbilityType &&
EffectType == Other.EffectType &&
CostType == Other.CostType &&
Output == Other.Output &&
Magnitude == Other.Magnitude &&
Multiplier == Other.Multiplier &&
Duration == Other.Duration &&
CooldownTime == Other.CooldownTime &&
Cost == Other.Cost;
}

FString GetTitle() const { return Title; }
FString GetDescription() const { return Description; }
EAbilityType GetAbilityType() const { return AbilityType; }
EAbilityEffectType GetEffectType() const { return EffectType; }
EAbilityCostType GetCostType() const { return CostType; }
float GetOutput() const { return Output; }
float GetMagnitude() const { return Magnitude; }
float GetMultiplier() const { return Multiplier; }
float GetDuration() const { return Duration; }
float GetCooldownTime() const { return CooldownTime; }
float GetCost() const { return Cost; }

void SetTitle(const FString& InTitle) { Title = InTitle; }
void SetDescription(const FString& InDescription) { Description = InDescription; }
void SetAbilityType(EAbilityType InAbilityType) { AbilityType = InAbilityType; }
void SetEffectType(EAbilityEffectType InEffectType) { EffectType = InEffectType; }
void SetCostType(EAbilityCostType InCostType) { CostType = InCostType; }
void SetOutput(float InOutput) { Output = InOutput; }
void SetMagnitude(float InMagnitude) { Magnitude = InMagnitude; }
void SetMultiplier(float InMultiplier) { Multiplier = InMultiplier; }
void SetDuration(float InDuration) { Duration = InDuration; }
void SetCooldownTime(float InCooldownTime) { CooldownTime = InCooldownTime; }
void SetCost(float InCost) { Cost = InCost; }
};

USTRUCT(BlueprintType)
struct FCharacterAbilityModule
{
GENERATED_BODY()

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)		
FString Title;

UPROPERTY(EditAnywhere, BlueprintReadWrite)		
FString Description;

UPROPERTY(EditAnywhere, BlueprintReadWrite)		
ECharacterAbilityType AbilityType;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
EAbilityEffectType EffectType;

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "EffectType == EAbilityEffectType::Damage", EditConditionHides))
EDamageType DamageType;

UPROPERTY(EditAnywhere, BlueprintReadWrite)		
FVector2D PowerRange;

UPROPERTY(EditAnywhere, BlueprintReadWrite) 	
FVector2D DurationRange;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FVector2D CooldownTimeRange;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
EAbilityCostType CostType;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FVector2D CostRange;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float Range;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float Radius;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
UAnimMontage* AbilityMontage;

private:
// Runtime cooldown timer
float CooldownTimer = 0.0f;

public:
// Constructor 
FCharacterAbilityModule()
: Title("DefaultAbility")
, Description("DefaultAbilityDescription")
, AbilityType(ECharacterAbilityType::Null)
, DamageType(EDamageType::Null)
, PowerRange(FVector2D::ZeroVector)
, DurationRange(FVector2D::ZeroVector)
, CooldownTimeRange(FVector2D::ZeroVector)
, CostType(EAbilityCostType::Null)
, CostRange(FVector2D::ZeroVector)
, Range(0.f)
, Radius(0.f)
, AbilityMontage(nullptr)
, CooldownTimer(0.0f)
{}

// Equality operators
bool operator==(const FCharacterAbilityModule& Other) const
{
return
Title == Other.Title &&
Description == Other.Description &&
AbilityType == Other.AbilityType &&
DamageType == Other.DamageType &&
PowerRange == Other.PowerRange &&
DurationRange == Other.DurationRange &&
CooldownTimeRange == Other.CooldownTimeRange &&
CostType == Other.CostType &&
CostRange == Other.CostRange &&
Range == Other.Range &&
Radius == Other.Radius &&
AbilityMontage == Other.AbilityMontage && 
CooldownTimer == Other.CooldownTimer;
}

// Inequality operators
bool operator!=(const FCharacterAbilityModule& Other) const
{
return !(*this == Other);
}

FString GetTitle() const { return Title; }
FString GetDescription() const { return Description; }
ECharacterAbilityType GetAbilityType() const { return AbilityType; }
EAbilityEffectType GetEffectType() const { return EffectType; }
EDamageType GetDamageType() const { return DamageType; }
FVector2D GetPowerRange() const { return PowerRange; }
FVector2D GetDurationRange() const { return DurationRange; }
FVector2D GetCooldownTimeRange() const { return CooldownTimeRange; }
EAbilityCostType GetCostType() const { return CostType; }
FVector2D GetCostRange() const { return CostRange; }
float GetRange() const { return Range; }
float GetRadius() const { return Radius; }
UAnimMontage* GetAbilityMontage() const { return AbilityMontage; }
float GetCooldownTimer() const { return CooldownTimer; }

// Update the cooldown timer
void CooldownTimerUpdate(float DeltaTime)
{
if (CooldownTimer > 0.f)
{
CooldownTimer -= DeltaTime;
if (CooldownTimer < 0.f)
{
  CooldownTimer = 0.f;
}
}
}

void StartCooldown()
{
CooldownTimer = GetRandomCooldownTime();
}

float GetRandomPower() const { return FMath::FRandRange(PowerRange.X, PowerRange.Y); }
float GetRandomDuration() const { return FMath::FRandRange(DurationRange.X, DurationRange.Y); }
float GetRandomCooldownTime() const { return FMath::FRandRange(CooldownTimeRange.X, CooldownTimeRange.Y); }
float GetRandomCost() const { return FMath::FRandRange(CostRange.X, CostRange.Y); }
bool IsAbilityOnCooldown() const { return CooldownTimer > 0.f; }

void SetTitle(const FString& InTitle) { Title = InTitle; }
void SetDescription(const FString& InDescription) { Description = InDescription; }
void SetAbilityType(ECharacterAbilityType InAbilityType) { AbilityType = InAbilityType; }
void SetEffectType(EAbilityEffectType InEffectType) { EffectType = InEffectType; }
void SetDamageType(EDamageType InDamageType) { DamageType = InDamageType; }
void SetPowerRange(const FVector2D& InPowerRange) { PowerRange = InPowerRange; }
void SetDurationRange(const FVector2D& InDurationRange) { DurationRange = InDurationRange; }
void SetCooldownTimeRange(const FVector2D& InCooldownTimeRange) { CooldownTimeRange = InCooldownTimeRange; }
void SetCostType(EAbilityCostType InCostType) { CostType = InCostType; }
void SetCostRange(const FVector2D& InCostRange) { CostRange = InCostRange; }
void SetRange(float InRange) { Range = InRange; }
void SetRadius(float InAreaRadius) { Radius = InAreaRadius; }
void SetAbilityMontage(UAnimMontage* InAbilityMontage) { AbilityMontage = InAbilityMontage; }
void SetCooldownTimer(float InCooldownTimer) { CooldownTimer = InCooldownTimer; }
};

USTRUCT(BlueprintType)
struct FCharacterAbilityData
{
GENERATED_BODY()

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)
FCharacterAbilityModule CombatStrike;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FCharacterAbilityModule LaserPulse;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FCharacterAbilityModule PlasmaShield;

public:
FCharacterAbilityData()
: CombatStrike()
, LaserPulse()
, PlasmaShield()
{
InitializeCombatStrikeAbility();
InitializeLaserPulseAbility();
InitializePlasmaShieldAbility();
}

private:

// Initialize Abilities
void InitializeCombatStrikeAbility()
{
CombatStrike.SetTitle("Combat Strike");
CombatStrike.SetDescription("A powerful melee attack that deals significant damage to a single target.");
CombatStrike.SetAbilityType(ECharacterAbilityType::CombatStrike);
CombatStrike.SetEffectType(EAbilityEffectType::Damage);
CombatStrike.SetDamageType(EDamageType::Physical);
CombatStrike.SetPowerRange(FVector2D(10.0f, 15.f));
CombatStrike.SetDurationRange(FVector2D(0.0f, 0.0f));
CombatStrike.SetCooldownTimeRange(FVector2D(2.0f, 3.0f));
CombatStrike.SetCostType(EAbilityCostType::Energy);
CombatStrike.SetCostRange(FVector2D(8.f, 10.f));
CombatStrike.SetRange(100.0f);
CombatStrike.SetRadius(30.0f);
}

// Initialize Laser Pulse Ability
void InitializeLaserPulseAbility()
{
LaserPulse.SetTitle("Laser Pulse");
LaserPulse.SetDescription("Fires a concentrated beam of energy that damages enemies in its path.");
LaserPulse.SetAbilityType(ECharacterAbilityType::LaserPulse);
LaserPulse.SetEffectType(EAbilityEffectType::Damage);
LaserPulse.SetDamageType(EDamageType::Energy);
LaserPulse.SetPowerRange(FVector2D(8.0f, 12.f));
LaserPulse.SetDurationRange(FVector2D(0.f, 0.f));
LaserPulse.SetCooldownTimeRange(FVector2D(2.f, 4.f));
LaserPulse.SetCostType(EAbilityCostType::Energy);
LaserPulse.SetCostRange(FVector2D(7.f, 12.f));
LaserPulse.SetRange(500.0f);
LaserPulse.SetRadius(20.0f);
}

// Initialize Plasma Shield Ability
void InitializePlasmaShieldAbility()
{
PlasmaShield.SetTitle("Plasma Shield");
PlasmaShield.SetDescription("Generates a protective shield that absorbs incoming damage for a short duration.");
PlasmaShield.SetAbilityType(ECharacterAbilityType::PlasmaShield);
PlasmaShield.SetEffectType(EAbilityEffectType::Defense);
PlasmaShield.SetDamageType(EDamageType::Null);
PlasmaShield.SetPowerRange(FVector2D(0.f, 0.f));
PlasmaShield.SetDurationRange(FVector2D(5.f, 10.f));
PlasmaShield.SetCooldownTimeRange(FVector2D(10.f, 15.f));
PlasmaShield.SetCostType(EAbilityCostType::Energy);
PlasmaShield.SetCostRange(FVector2D(15.f, 25.f));
PlasmaShield.SetRange(0.0f);
PlasmaShield.SetRadius(0.0f);
}

public:
FCharacterAbilityModule FindCharacterAbilityByType(ECharacterAbilityType AbilityType) const
{
switch (AbilityType)
{
case ECharacterAbilityType::CombatStrike:
return CombatStrike;
case ECharacterAbilityType::LaserPulse:
return LaserPulse;
case ECharacterAbilityType::PlasmaShield:
return PlasmaShield;
default:
return FCharacterAbilityModule();
}
}

const FCharacterAbilityModule* FindCharacterAbilityByTypePtr(ECharacterAbilityType AbilityType) const
{
switch (AbilityType)
{
case ECharacterAbilityType::CombatStrike:
return &CombatStrike;

case ECharacterAbilityType::LaserPulse:
return &LaserPulse;

case ECharacterAbilityType::PlasmaShield:
return &PlasmaShield;

default:
return nullptr;
}
}

};

#pragma endregion

#pragma region Level

USTRUCT(BlueprintType)
struct FCharacterLevelData
{
GENERATED_BODY()

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float Experience;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
TArray<float> ExperienceThreshold;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
int32 Level;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
int32 MaxLevel;

// This experience bonus when enemy is defeated to increase XP gain for player
float ExperienceRewardBonus;

private:
// Initialize Experience Thresholds for Leveling Up
void InitializeExperienceThresholds()
{
ExperienceThreshold.Empty();

const int32 MaximumLevel = MaxLevel;
const int32 MaxIndex = MaximumLevel + 1; // Include Level 0
const int32 NumSegments = 10;
const float BaseStep = 100.f; // Level 1 starts at 101
const float StepMultiplier = 1.1f;

ExperienceThreshold.Add(0); // Level 0

int32 LevelsPerSegment = MaximumLevel / NumSegments;
float CurrentThreshold = 0.f;
float CurrentStep = BaseStep;

for (int32 Segment = 0; Segment < NumSegments; ++Segment)
{
for (int32 LevelInSegment = 0; LevelInSegment < LevelsPerSegment; ++LevelInSegment)
{
  CurrentThreshold += CurrentStep;

  // Round nicely, e.g., nearest 10
  int32 RoundedThreshold = FMath::RoundToInt(CurrentThreshold / 10.f) * 10;
  ExperienceThreshold.Add(RoundedThreshold);
}

CurrentStep *= StepMultiplier;
}

// Fill remaining levels if MaxLevel not divisible by segments
int32 RemainingLevels = MaximumLevel - (ExperienceThreshold.Num() - 1);
for (int32 i = 0; i < RemainingLevels; ++i)
{
CurrentThreshold += CurrentStep;
int32 RoundedThreshold = FMath::RoundToInt(CurrentThreshold / 10.f) * 10;
ExperienceThreshold.Add(RoundedThreshold);
}
}


public:
// Constructor
FCharacterLevelData()
: Experience(0.f)
, Level(0)
, MaxLevel(100)
, ExperienceRewardBonus(30.f)
{
InitializeExperienceThresholds();
}

// Getter for current experience 
float GetExperience() const
{
return Experience;
}

// Getter for experience thresholds
TArray<float> GetExperienceThreshold() const
{
return ExperienceThreshold;
}

// Getter for current level
int32 GetLevel() const
{
return Level;
}

// Getter for maximum level
int32 GetMaxLevel() const
{
return MaxLevel;
}

// Getter for experience reward bonus
int32 GetExperienceRewardBonus() const
{
int32 CurrentLevel = Level;
int32 NextLevelExperience = ExperienceThreshold.IsValidIndex(CurrentLevel) ? ExperienceThreshold[CurrentLevel] : 0;

int32 RewardBonus = FMath::RoundToInt(ExperienceRewardBonus + (CurrentLevel * 2) + (NextLevelExperience / 100.f));

return RewardBonus;
}

// Getter for maximum level
void SetExperience(float InExperience)
{
Experience = FMath::Max(0.f, InExperience);

int32 CurrentLevelIndex = Level - 1;
float ExperienceToNextLevel = 0.f;

if (ExperienceThreshold.IsValidIndex(CurrentLevelIndex))
{
ExperienceToNextLevel = ExperienceThreshold[CurrentLevelIndex];
}
}

// Setter for experience thresholds
void SetExperienceThreshold(const TArray<float>& InThreshold)
{
ExperienceThreshold = InThreshold;
}

// Setter for maximum level
void SetLevel(int32 InLevel)
{
Level = FMath::Clamp(InLevel, 1, MaxLevel);
}

// Setter for maximum level
void SetMaxLevel(int32 InMaxLevel)
{
MaxLevel = InMaxLevel;
}

// Setter for experience reward bonus
void SetExperienceRewardBonus(float InBonus)
{
ExperienceRewardBonus = InBonus;
}

// Increase Experience
void IncreaseExperience(float Amount)
{
if (Amount <= 0.f || Level >= MaxLevel)
{
return;
}

SetExperience(Experience + Amount);

while (Level < MaxLevel)
{
const int32 ThresholdIndex = Level - 1;

if (!ExperienceThreshold.IsValidIndex(ThresholdIndex))
{
  break;
}

const float RequiredXP = ExperienceThreshold[ThresholdIndex];

if (Experience < RequiredXP)
{
  break;
}

// Consume XP required for this level
SetExperience(Experience - RequiredXP);

// Level up
SetLevel(Level + 1);
}
}

// Decrease Experience
void DecreaseExperience(float Amount)
{
SetExperience(FMath::Max(0.f, Experience - Amount));
}

// Level Up
void LevelUp()
{
if (Level < MaxLevel)
{
int32 NextLevel = Level + 1;
SetLevel(NextLevel);
}
}
};

#pragma endregion

#pragma region Movement 
USTRUCT(BlueprintType)
struct FCharacterMovementData
{
GENERATED_BODY()

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float WalkSpeed;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float DefaultSpeed;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float MaxSpeed;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
bool bEnableSprint;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
bool bEnableJump;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
bool bEnableDoubleJump;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
int32 MaxJumpCount;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
float JumpHeight;

public:
FCharacterMovementData()
: WalkSpeed(150.0f)
, DefaultSpeed(300.0f)
, MaxSpeed(600.0f)
, bEnableSprint(true)
, bEnableJump(true)
, bEnableDoubleJump(false)
, MaxJumpCount(1)
, JumpHeight(420.f)
{
}

float GetWalkSpeed() const { return WalkSpeed; }
float GetDefaultSpeed() const { return DefaultSpeed; }
float GetMaxSpeed() const { return MaxSpeed; }
bool IsSprintEnabled() const { return bEnableSprint; }
bool IsJumpEnabled() const { return bEnableJump; }
bool IsDoubleJumpEnabled() const { return bEnableDoubleJump; }
int32 GetMaxJumpCount() const { return MaxJumpCount; }
float GetJumpHeight() const { return JumpHeight; }
void SetWalkSpeed(float InWalkSpeed) { WalkSpeed = InWalkSpeed; }
void SetDefaultSpeed(float InDefaultSpeed) { DefaultSpeed = InDefaultSpeed; }
void SetMaxSpeed(float InMaxSpeed) { MaxSpeed = InMaxSpeed; }
void SetEnableSprint(bool bInEnableSprint) { bEnableSprint = bInEnableSprint; }
void SetEnableJump(bool bInEnableJump) { bEnableJump = bInEnableJump; }
void SetEnableDoubleJump(bool bInEnableDoubleJump) { bEnableDoubleJump = bInEnableDoubleJump; }
void SetMaxJumpCount(int32 InMaxJumpCount) { MaxJumpCount = InMaxJumpCount; }
void SetJumpHeight(float InJumpHeight) { JumpHeight = InJumpHeight; }
};

#pragma endregion

#pragma region Character

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
Null		UMETA(DisplayName = "Select Character State"),
Idle		UMETA(DisplayName = "Idle"),
Attacking	UMETA(DisplayName = "Attacking"),
Defending	UMETA(DisplayName = "Defending"),
Death		UMETA(DisplayName = "Death"),
Stunned		UMETA(DisplayName = "Stunned"),
Charging	UMETA(DisplayName = "Charging"),
Max			UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
Null 	UMETA(DisplayName = "Select Character Type"),
Player	UMETA(DisplayName = "Player"),
AI		UMETA(DisplayName = "AI"),
Max     UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FCharacterData
{
GENERATED_BODY()

protected:
UPROPERTY(EditAnywhere, BlueprintReadWrite)
ECharacterState State;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
ECharacterType Type;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FInformationData Information;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FCharacterAttribute AttributeData;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FCharacterAbilityData AbilityData;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FProtectionData ProtectionData;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FCharacterLevelData LevelData;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
FCharacterMovementData MovementData;

public:
// Constructor
FCharacterData()
: State(ECharacterState::Idle)
, Type(ECharacterType::Null)
, Information()
, AttributeData()
, AbilityData()
, ProtectionData()
, LevelData()
, MovementData()
{}

// Getters and Setters
ECharacterState& GetCharacterState() { return State; }
ECharacterType& GetCharacterType()  { return Type; }
FInformationData& GetInformationData() { return Information; }
FCharacterAttribute& GetAttributeData() { return AttributeData; }
FCharacterAbilityData& GetAbilityData() { return AbilityData; }
FProtectionData& GetProtectionData() { return ProtectionData; }
FCharacterLevelData& GetLevelData() { return LevelData; }
FCharacterMovementData& GetMovementData()  { return MovementData; }

// Setters
void SetCharacterState(ECharacterState InState) {State = InState; }
void SetCharacterType(ECharacterType InType) {	Type = InType;	}
void SetInformationData(const FInformationData& InInformation) { Information = InInformation; }
void SetAttributeData(const FCharacterAttribute& InAttribute) { AttributeData = InAttribute; }
void SetAbilityData(const FCharacterAbilityData& InAbility) { AbilityData = InAbility; }
void SetProtectionData(const FProtectionData& InProtection) { ProtectionData = InProtection; }
void SetLevelData(const FCharacterLevelData& InLevel) { LevelData = InLevel; }
void SetMovementData(const FCharacterMovementData& InMovement) { MovementData = InMovement; }

/*Validate*/
bool IsPlayer() const { return Type == ECharacterType::Player; }
bool IsAI() const { return Type == ECharacterType::AI; }
};

#pragma endregion
