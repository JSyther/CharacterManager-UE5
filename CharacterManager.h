// ============================================================================
// CharacterManager.h
// ============================================================================
// Central character management component responsible for:
//
// - Character state & type handling
// - Attribute access, mutation and regeneration
// - Ability, protection and level data access
// - Delegate broadcasting for UI / gameplay systems
//
// This component acts as the single source of truth for character-related
// gameplay data and events.
//
// Designed to be engine-agnostic, modular and Blueprint-friendly.
// ============================================================================
// NOTE:
// This system is a work in progress and will be expanded incrementally.
// Some features are intentionally incomplete at this stage.
//
// The CharacterManager depends on an external structured data package
// (CharacterData and related modules), which must be properly defined
// and integrated for full functionality. 
// Link: 
// ============================================================================



UCLASS(BlueprintType)
class NERBY_API UCharacterManager : public UActorComponent
{
	GENERATED_BODY()

#pragma region Delegate

public:
	/*CharacterState*/
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnCharacterStateChangedSignature OnCharacterStateChanged;

	/*CharacterType*/
	// Delegate for health attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnCharacterTypeChangedSignature OnCharacterTypeChanged;

	/*Information*/
	// Delegate for title is changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnCharacterTitleChangedSignature OnCharacterTitleChanged;

	// Delegate for description is changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnCharacterDescriptionChangedSignature OnCharacterDescriptionChanged;

	/*Attribute*/
	// Delegate for health attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnHealthAttributeChangedSignature OnHealthAttributeChanged;

	// Delegate for stamina attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnStaminaAttributeChangedSignature OnStaminaAttributeChanged;

	// Delegate for energy attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnEnergyAttributeChangedSignature OnEnergyAttributeChanged;

	// Delegate for shield attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnShieldAttributeChangedSignature OnShieldAttributeChanged;

	// Delegate for output attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnOutputAttributeChangedSignature OnOutputAttributeChanged;

	// Delegate for actuation attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnActuationAttributeChangedSignature OnActuationAttributeChanged;

	// Delegate for integrity attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnIntegrityAttributeChangedSignature OnIntegrityAttributeChanged;

	// Delegate for capacity attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnCapacityAttributeChangedSignature OnCapacityAttributeChanged;

	// Delegate for regeneration attribute changed event
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnRegenerationAttributeChangedSignature OnRegenerationAttributeChanged;

	/*Ability*/
	// Delegate for combat strike executed event
	UPROPERTY(BlueprintAssignable, Category = "Level")
	FOnCombatStrikeExecutedSignature OnCombatStrikeExecuted;

	// Delegate for laser pulse executed event
	UPROPERTY(BlueprintAssignable, Category = "Level")
	FOnLaserPulseExecutedSignature OnLaserPulseExecuted;

	// Delegate for plasma shield executed event
	UPROPERTY(BlueprintAssignable, Category = "Level")
	FOnPlasmaShieldExecutedSignature OnPlasmaShieldExecuted;

private:
	// Setup delegates
	void SetupDelegates();

	// Bind character state changed delegate
	UFUNCTION()
	void BindOnCharacterStateChanged(ECharacterState NewCharacterState);

	// Bind health attribute changed delegate
	UFUNCTION()
	void BindOnHealthAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind stamina attribute changed delegate
	UFUNCTION()
	void BindOnStaminaAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind energy attribute changed delegate
	UFUNCTION()
	void BindOnEnergyAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind shield attribute changed delegate
	UFUNCTION()
	void BindOnShieldAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind output attribute changed delegate
	UFUNCTION()
	void BindOnOutputAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind actuation attribute changed delegate
	UFUNCTION()
	void BindOnActuationAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind integrity attribute changed delegate
	UFUNCTION()
	void BindOnIntegrityAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind capacity attribute changed delegate
	UFUNCTION()
	void BindOnCapacityAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

	// Bind regeneration attribute changed delegate
	UFUNCTION()
	void BindOnRegenerationAttributeChanged(float MinValue, float MaxValue, float CurrentValue);

#pragma endregion

#pragma region Constructor

public:
	// Constructor 
	UCharacterManager();

#pragma endregion

#pragma region BeginPlay

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Tick 

protected:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Debug

protected:
	// Debug Tick
	void DebugTick(FCharacterDebugData& Debug, const FString& Context, const FString& Message);

#pragma endregion

#pragma region OwnerCharacter

protected:
	// Owner Character Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Owner")
	TObjectPtr<ACharacterModule> OwnerCharacter;

public:
	UFUNCTION(BlueprintCallable, Category = "Owner")
	ACharacterModule* GetOwnerCharacter() const
	{
		return OwnerCharacter;
	}

	// Returns the owner character
	void SetOwnerCharacter(ACharacterModule* NewOwner)
	{
		OwnerCharacter = NewOwner;
	}

#pragma endregion

#pragma region CharacterData

protected:
	// Character data 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FCharacterData CharacterData;

public:
	// Returns a COPY of the character data (read-only, safe).
	// If pointer is null, returns a default-constructed struct.
	UFUNCTION(BlueprintCallable, Category = "Data")
	FCharacterData& GetCharacterData()
	{
		return CharacterData;
	}

	// Returns a read-only reference to the character data.
	FCharacterData GetCharacterDataReadOnly() const
	{
		return CharacterData;
	}

	// Returns a mutable reference to the character data.
	// WARNING: Caller must ensure CharacterData is valid.
	FCharacterData& GetMutableCharacterData()
	{
		return CharacterData;
	}

	// Returns the raw pointer to the character data.
	FCharacterData* GetCharacterDataPtr() const
	{
		FCharacterData* CharacterDataPtr = const_cast<FCharacterData*>(&CharacterData);

		return CharacterDataPtr;
	}

	// Sets character data by copying into an existing pointer.
	// Allocates memory if needed.
	UFUNCTION(BlueprintCallable, Category = "Data")
	void SetCharacterData(const FCharacterData& NewData)
	{
		CharacterData = NewData;
	}

#pragma endregion

#pragma region CharacterState

public:
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetCharacterState(ECharacterState NewState);

	// Returns the character state
	UFUNCTION(BlueprintCallable, Category = "State")
	ECharacterState GetCharacterState();

private:
	// Handles character death state
	void HandleOnDeathState();

#pragma endregion

#pragma region CharacterType

public:
	// Returns the character type
	UFUNCTION(BlueprintCallable, Category = "Type")
	ECharacterType GetCharacterType();

	// Sets the character type
	UFUNCTION(BlueprintCallable, Category = "Type")
	void SetCharacterType(ECharacterType NewType);

	// Checks if the character is a player character
	UFUNCTION(BlueprintCallable, Category = "Type")
	bool IsPlayerCharacter();

	// Checks if the character is an AI character
	UFUNCTION(BlueprintCallable, Category = "Type")
	bool IsAICharacter();

#pragma endregion

#pragma region Information

public:
	// Returns the character's title
	UFUNCTION(BlueprintCallable, Category = "Character|Progression")
	FString GetTitle();

	// Returns the character's description
	UFUNCTION(BlueprintCallable, Category = "Character|Progression")
	FString GetDescription();

	// Sets the character's title
	UFUNCTION(BlueprintCallable, Category = "Character|Progression")
	void SetTitle(const FString& NewTitle);

	// Sets the character's description
	UFUNCTION(BlueprintCallable, Category = "Character|Progression")
	void SetDescription(const FString& NewDescription);

#pragma endregion

#pragma region Attribute

public:
	/*General*/
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetCurrentAttributeValueByType(ECharacterAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetMinimumAttributeValueByType(ECharacterAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetMaximumAttributeValueByType(ECharacterAttributeType AttributeType);

	/*Primary Attribute*/

	/*
	* Accessor
	*/

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	FAttributeModule GetPrimaryAttributeModuleByType(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetPrimaryAttributeCurrentValueByType(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetPrimaryAttributeMinimumValueByType(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetPrimaryAttributeMaximumValueByType(EPrimaryAttributeType AttributeType);

	/*
	* Mutator
	*/

	/*Secondary Attribute*/

	/*
	* Accessor
	*/
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	FAttributeModule GetSecondaryAttributeModuleByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetSecondaryAttributeCurrentValueByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetSecondaryAttributeMinimumValueByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetSecondaryAttributeMaximumByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetMaximumAttributeByType(ECharacterAttributeType AttributeType);

	/*
	* Mutator
	*/
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetPrimaryAttributeValueByType(EPrimaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetSecondaryAttributeValueByType(ESecondaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool HasPrimaryAttributeValue(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool HasSecondaryAttributeValue(ESecondaryAttributeType AttributeType);


/*Update*/
	// Update Primary Attribute Current Value By Type
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void UpdatePrimaryAttributeCurrentValueByType(EPrimaryAttributeType AttributeType, float DeltaValue, float Amount);


	// Update Primary Attributes (Called every tick)
	void UpdatePrimaryAttributes(float DeltaTime);

#pragma endregion

#pragma region Ability 

public:
	// Ability management functions can be added here
	UFUNCTION(BlueprintCallable, Category = "Ability")
	FCharacterAbilityModule GetCharacterAbilityModuleByType(ECharacterAbilityType AbilityType);

	FString GetCharacterAbilityTitleByType(ECharacterAbilityType AbilityType);
	FString GetCharacterAbilityDescriptionByType(ECharacterAbilityType AbilityType);
	ECharacterAbilityType GetAbilityTypeByType(ECharacterAbilityType AbilityType);
	FVector2D GetAbilityPowerRangeByType(ECharacterAbilityType AbilityType);
	FVector2D GetAbilityDurationRangeByType(ECharacterAbilityType AbilityType);
	FVector2D GetAbilityCooldownTimeRangeByType(ECharacterAbilityType AbilityType);
	EAbilityCostType GetAbilityCostTypeByType(ECharacterAbilityType AbilityType);
	FVector2D GetAbilityCostRangeByType(ECharacterAbilityType AbilityType);
	float GetAbilityRangeByType(ECharacterAbilityType AbilityType);
	float GetAbilityAreaRadiusByType(ECharacterAbilityType AbilityType);

	float GetAbilityRandomPowerByType(ECharacterAbilityType AbilityType);
	float GetAbilityRandomDurationByType(ECharacterAbilityType AbilityType);
	float GetAbilityRandomCooldownTimeByType(ECharacterAbilityType AbilityType);
	float GetAbilityRandomCostByType(ECharacterAbilityType AbilityType);

	void SetCharacterAbilityModuleByType(ECharacterAbilityType AbilityType, const FCharacterAbilityModule& NewAbilityModule);
	void SetCharacterAbilityTitleByType(ECharacterAbilityType AbilityType, const FString& NewTitle);
	void SetCharacterAbilityDescriptionByType(ECharacterAbilityType AbilityType, const FString& NewDescription);
	void SetAbilityPowerRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewPowerRange);
	void SetAbilityDurationRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewDurationRange);
	void SetAbilityCooldownTimeRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewCooldownTimeRange);
	void SetAbilityCostRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewCostRange);
	void SetAbilityRangeByType(ECharacterAbilityType AbilityType, float NewRange);
	void SetAbilityAreaRadiusByType(ECharacterAbilityType AbilityType, float NewRadius);

#pragma endregion

#pragma region Protection

public:
	// Protection management functions can be added here
	UFUNCTION(BlueprintCallable, Category = "Protection")
	EProtectionType GetProtectionTypeByType(EProtectionType Type);

	UFUNCTION(BlueprintCallable, Category = "Protection")
	FString GetTitleByType(EProtectionType Type);

	UFUNCTION(BlueprintCallable, Category = "Protection")
	FString GetDescriptionByType(EProtectionType Type);

	UFUNCTION(BlueprintCallable, Category = "Protection")
	float GetValueByType(EProtectionType Type);

	UFUNCTION(BlueprintCallable, Category = "Protection")
	float GetMultiplierByType(EProtectionType Type);

	UFUNCTION(BlueprintCallable, Category = "Protection")
	float GetAmplifierByType(EProtectionType Type);

	UFUNCTION(BlueprintCallable, Category = "Protection")
	float GetRandomFinalProtectionByType(EProtectionType Type);

#pragma endregion

#pragma region Level

public:
	// Level management functions can be added here
	UFUNCTION(BlueprintCallable, Category = "Level")
	FCharacterLevelData& GetLevelData();

	// Returns the current experience
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetCurrentExperience();

	// Returns the experience threshold for the next level
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetNextLevelExperienceThreshold();

	// Returns the current level
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetLevel();

	// Returns the maximum level
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetMaxLevel();

	// Returns the experience reward bonus
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetExperienceRewardBonus();

	// Increase Experience
	UFUNCTION(BlueprintCallable, Category = "Level")
	void AddExperience(float Amount);

	// Level Up Function
	UFUNCTION(BlueprintCallable, Category = "Level")
	void LevelUp();

#pragma endregion

#pragma region Movement

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetWalkSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetDefaultSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMaximumSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsSprintEnabled();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsJumpEnabled();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsDoubleJumpEnabled();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	int32 GetMaxJumpCount();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetJumpHeight();

#pragma endregion

#pragma region Damage

public:
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ExecuteDamage(ACharacterModule* TargetCharacter, float InstigatorDamage, float TargetProtection);

#pragma endregion

#pragma region PrimaryAttribute

public:
	// Regenerate primary attribute over time
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ExecutePrimaryAttributeRegeneration(ACharacterModule* TargetCharacter, EPrimaryAttributeType Type, float Amount);

private:
	// Timer handle for primary attribute regeneration
	FTimerHandle PrimaryAttributeRegenerationTimerHandle;

	// Remaining amount to regenerate
	ACharacterModule* RegenTarget = nullptr;
	EPrimaryAttributeType RegenType;
	float RemainingRegenAmount = 0.f;

	UFUNCTION()
	void HandleExecutePrimaryAttributeRegenerationHandler();

#pragma endregion

};
