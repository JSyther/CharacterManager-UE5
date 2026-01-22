#pragma region CharacterManager

#pragma region Delegate

void UCharacterManager::SetupDelegates()
{
	/*State*/
	OnCharacterStateChanged.AddDynamic(this, &UCharacterManager::BindOnCharacterStateChanged);
	
	// Health
	OnHealthAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnHealthAttributeChanged);
	
	// Stamina
	OnStaminaAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnStaminaAttributeChanged);
	
	// Energy
	OnEnergyAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnEnergyAttributeChanged);
	
	// Shield
	OnShieldAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnShieldAttributeChanged);
	
	// Output
	OnOutputAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnOutputAttributeChanged);
	
	// Actuation
	OnActuationAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnActuationAttributeChanged);
	
	// Integrity
	OnIntegrityAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnIntegrityAttributeChanged);
	
	// Capacity
	OnCapacityAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnCapacityAttributeChanged);
	
	// Regeneration
	OnRegenerationAttributeChanged.AddDynamic(this, &UCharacterManager::BindOnRegenerationAttributeChanged);
}

void UCharacterManager::BindOnCharacterStateChanged(ECharacterState NewCharacterState)
{
	switch (NewCharacterState)
	{
		case ECharacterState::Idle:
			break;
		case ECharacterState::Attacking:
			break;
		case ECharacterState::Defending:
			break;
		case ECharacterState::Death:
			HandleOnDeathState();
			break;
		case ECharacterState::Stunned:
			break;
		case ECharacterState::Charging:
			break;

		default:
			break;
	}
}

void UCharacterManager::BindOnHealthAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnStaminaAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Stamina Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnEnergyAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Energy Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnShieldAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Shield Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnOutputAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Output Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnActuationAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Actuation Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnIntegrityAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Integrity Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnCapacityAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Capacity Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

void UCharacterManager::BindOnRegenerationAttributeChanged(float MinValue, float MaxValue, float CurrentValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Regeneration Attribute Changed: Min: %f, Max: %f, Current: %f"), MinValue, MaxValue, CurrentValue);
}

#pragma endregion

#pragma region Constructor

UCharacterManager::UCharacterManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetupDelegates();
}

#pragma endregion

#pragma region BeginPlay

void UCharacterManager::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

#pragma region Tick 

void UCharacterManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UpdatePrimaryAttributes(DeltaTime);
}

void UCharacterManager::DebugTick(FCharacterDebugData& Debug, const FString& Context, const FString& Message)
{
	if (!Debug.bEnableLog || !GetWorld())
	{
		return;
	}

	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	Debug.LogTimer += DeltaTime;
	Debug.LogAccumulatedTime += DeltaTime;

	if(Debug.LogTimer >= Debug.LogInterval && Debug.LogAccumulatedTime <= Debug.LogDuration)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("[%s] %s"),
			*Context,
			*Message
		);

		Debug.LogTimer = 0.0f;
		Debug.LogAccumulatedTime = 0.0f;
	}
}

#pragma endregion

#pragma region CharacterState

void UCharacterManager::SetCharacterState(ECharacterState NewState)
{
	CharacterData.SetCharacterState(NewState);
	OnCharacterStateChanged.Broadcast(NewState);
}

ECharacterState UCharacterManager::GetCharacterState()
{
	return CharacterData.GetCharacterState();
}

void UCharacterManager::HandleOnDeathState()
{
	check(OwnerCharacter);

	bool AI = CharacterData.IsAI();
	bool Player = CharacterData.IsPlayer();

	if (Player)
	{
		OwnerCharacter->PlayerHandleOnDeathState();
	}
	else if (AI)
	{
		OwnerCharacter->AIHandleOnDeathState();
	}
	else
	{
		#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("HandleOnDeathState: Character Type is not valid."));
		#endif
	}
}

#pragma endregion

#pragma region CharacterType

ECharacterType UCharacterManager::GetCharacterType()
{

	return CharacterData.GetCharacterType();
}

void UCharacterManager::SetCharacterType(ECharacterType NewType)
{
	CharacterData.SetCharacterType(NewType);
	OnCharacterTypeChanged.Broadcast(NewType);
}

bool UCharacterManager::IsPlayerCharacter()
{
	return CharacterData.GetCharacterType() == ECharacterType::Player;
}

bool UCharacterManager::IsAICharacter()
{
	return CharacterData.GetCharacterType() == ECharacterType::AI;
}

#pragma endregion

#pragma region Information

FString UCharacterManager::GetTitle()
{
	return CharacterData.GetInformationData().GetTitle();
}

FString UCharacterManager::GetDescription()
{
	return CharacterData.GetInformationData().GetDescription();
}

void UCharacterManager::SetTitle(const FString& NewTitle)
{
	CharacterData.GetInformationData().SetTitle(NewTitle);
	OnCharacterTitleChanged.Broadcast(NewTitle);
}

void UCharacterManager::SetDescription(const FString& NewDescription)
{
	CharacterData.GetInformationData().SetDescription(NewDescription);
	OnCharacterDescriptionChanged.Broadcast(NewDescription);
}

#pragma endregion

#pragma region Attribute

float UCharacterManager::GetCurrentAttributeValueByType(ECharacterAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ECharacterAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetCurrentAttributeValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;

	default:
		return 0.0f;
	}
}

float UCharacterManager::GetMinimumAttributeValueByType(ECharacterAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ECharacterAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetMinimumAttributeValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UCharacterManager::GetMaximumAttributeValueByType(ECharacterAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ECharacterAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetMaximumAttributeByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

FAttributeModule UCharacterManager::GetPrimaryAttributeModuleByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Health);
	case EPrimaryAttributeType::Energy:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Energy);
	case EPrimaryAttributeType::Shield:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Shield);
	case EPrimaryAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Stamina);
	case EPrimaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeModuleByType: Selected AttributeType is Null."));
#endif
		return FAttributeModule();
	default:
		return FAttributeModule();
	}
}

float UCharacterManager::GetPrimaryAttributeCurrentValueByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		return Health.GetCurrentValue();
	}
	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		return Energy.GetCurrentValue();
	}

	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		return Shield.GetCurrentValue();
	}

	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		return Stamina.GetCurrentValue();
	}

	case EPrimaryAttributeType::Null:
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeCurrentValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	}

	default:
		return 0.0f;
	}
}

float UCharacterManager::GetPrimaryAttributeMinimumValueByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		return Health.GetMinimumValue();
	}

	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		return Energy.GetMinimumValue();
	}

	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		return Shield.GetMinimumValue();
	}

	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		return Stamina.GetMinimumValue();
	}

	case EPrimaryAttributeType::Null:
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeMinimumValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	}

	default:
		return 0.0f;
	}
}

float UCharacterManager::GetPrimaryAttributeMaximumValueByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		return Health.GetMaximumValue();
	}

	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		return Energy.GetMaximumValue();
	}

	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		return Shield.GetMaximumValue();
	}

	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		return Stamina.GetMaximumValue();
	}

	case EPrimaryAttributeType::Null:
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeMaximumValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	}

	default:
		return 0.0f;
	}
}

FAttributeModule UCharacterManager::GetSecondaryAttributeModuleByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Output);
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Actuation);
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Integrity);
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Capacity);
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Regeneration);
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeModuleByType: Selected AttributeType is Null."));
#endif
		return FAttributeModule();
	default:
		return FAttributeModule();
	}
}

float UCharacterManager::GetSecondaryAttributeCurrentValueByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeCurrentValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UCharacterManager::GetSecondaryAttributeMinimumValueByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeMinimumValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UCharacterManager::GetSecondaryAttributeMaximumByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeMaximumByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UCharacterManager::GetMaximumAttributeByType(ECharacterAttributeType AttributeType)
{
	return GetMaximumAttributeValueByType(AttributeType);
}

void UCharacterManager::SetPrimaryAttributeValueByType(EPrimaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		Health.SetValue(MinValue, MaxValue, CurrentValue);
		OnHealthAttributeChanged.Broadcast(Health.GetMinimumValue(), Health.GetMaximumValue(), Health.GetCurrentValue());

		if(Health.GetCurrentValue() <= 0.0f)
		{
			SetCharacterState(ECharacterState::Death);
		}	

		break;
	}
	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		Energy.SetValue(MinValue, MaxValue, CurrentValue);
		OnEnergyAttributeChanged.Broadcast(Energy.GetMinimumValue(), Energy.GetMaximumValue(), Energy.GetCurrentValue());
		break;
	}
	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		Shield.SetValue(MinValue, MaxValue, CurrentValue);
		OnShieldAttributeChanged.Broadcast(Shield.GetMinimumValue(), Shield.GetMaximumValue(), Shield.GetCurrentValue());
		break;
	}
	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		Stamina.SetValue(MinValue, MaxValue, CurrentValue);
		OnStaminaAttributeChanged.Broadcast(Stamina.GetMinimumValue(), Stamina.GetMaximumValue(), Stamina.GetCurrentValue());
		break;
	}
	default:
		break;
	}
}

void UCharacterManager::SetSecondaryAttributeValueByType(ESecondaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue)
{
	switch (AttributeType)
	{
		case ESecondaryAttributeType::Output:
		{
			auto& Output = CharacterData.GetAttributeData().GetOutputAttributeModule();
			Output.SetValue(MinValue, MaxValue, CurrentValue);
			OnOutputAttributeChanged.Broadcast(Output.GetMinimumValue(), Output.GetMaximumValue(), Output.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Actuation:
		{
			auto& Actuation = CharacterData.GetAttributeData().GetActuationAttributeModule();
			Actuation.SetValue(MinValue, MaxValue, CurrentValue);
			OnActuationAttributeChanged.Broadcast(Actuation.GetMinimumValue(), Actuation.GetMaximumValue(), Actuation.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Integrity:
		{
			auto& Integrity = CharacterData.GetAttributeData().GetIntegrityAttributeModule();
			Integrity.SetValue(MinValue, MaxValue, CurrentValue);
			OnIntegrityAttributeChanged.Broadcast(Integrity.GetMinimumValue(), Integrity.GetMaximumValue(), Integrity.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Capacity:
		{
			auto& Capacity = CharacterData.GetAttributeData().GetCapacityAttributeModule();
			Capacity.SetValue(MinValue, MaxValue, CurrentValue);
			OnCapacityAttributeChanged.Broadcast(Capacity.GetMinimumValue(), Capacity.GetMaximumValue(), Capacity.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Regeneration:
		{
			auto& Regeneration = CharacterData.GetAttributeData().GetRegenerationAttributeModule();
			Regeneration.SetValue(MinValue, MaxValue, CurrentValue);
			OnRegenerationAttributeChanged.Broadcast(Regeneration.GetMinimumValue(), Regeneration.GetMaximumValue(), Regeneration.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Null:
		{
			#if WITH_EDITOR
			UE_LOG(LogTemp, Error, TEXT("SetSecondaryAttributeCurrentValueByType: Selected AttributeType is Null."));
			#endif
			break;
		}
	}
}

bool UCharacterManager::HasPrimaryAttributeValue(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Null:
	default:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("HasPrimaryAttributeValue: Invalid AttributeType."));
#endif
		return false;
	}
}

bool UCharacterManager::HasSecondaryAttributeValue(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Null:
	default:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("HasSecondaryAttributeValue: Invalid AttributeType."));
#endif
		return false;
	}
}

void UCharacterManager::UpdatePrimaryAttributeCurrentValueByType(EPrimaryAttributeType AttributeType, float DeltaValue, float Amount)
{
	switch (AttributeType)
	{
		case EPrimaryAttributeType::Health:
		{
			// Update Health
			auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();

			// Store current health before update
			float CurrentHealth = Health.GetCurrentValue();
			float MaxHealth = Health.GetMaximumValue();

			if(CurrentHealth >= MaxHealth)
			{
				// No need to update if health is already at maximum
				return; 
			}

			float NewHealth = CurrentHealth + (DeltaValue * Amount);

			// Clamp new health value within min and max bounds
			SetPrimaryAttributeValueByType(EPrimaryAttributeType::Health, Health.GetMinimumValue(), Health.GetMaximumValue(), NewHealth);
			break;
		}

		case EPrimaryAttributeType::Energy:
		{
			// Update Energy
			auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();

			// Store current energy before update
			float CurrentEnergy = Energy.GetCurrentValue();
			float MaxEnergy = Energy.GetMaximumValue();

			if (CurrentEnergy >= MaxEnergy)
			{
				return;
			}

			float NewEnergy = CurrentEnergy + (DeltaValue * Amount);

			SetPrimaryAttributeValueByType(EPrimaryAttributeType::Energy, Energy.GetMinimumValue(), Energy.GetMaximumValue(), NewEnergy);
			break;
		}

		case EPrimaryAttributeType::Shield:
		{
			// Update Shield
			auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();

			// Store current shield before update
			float CurrentShield = Shield.GetCurrentValue();

			if(CurrentShield >= Shield.GetMaximumValue())
			{
				// No need to update if shield is already at maximum
				return; 
			}

			float NewShield = CurrentShield + (DeltaValue * Amount);

			OnShieldAttributeChanged.Broadcast(Shield.GetMinimumValue(), Shield.GetMaximumValue(), NewShield);
			break;
		}

		case EPrimaryAttributeType::Stamina:
		{
			// Update Stamina
			auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();

			// Store current stamina before update
			float CurrentStamina = Stamina.GetCurrentValue();
			float MaxStamina = Stamina.GetMaximumValue();

			if (CurrentStamina >= MaxStamina)
			{
				// No need to update if stamina is already at maximum
				return; 
			}

			float NewStamina = CurrentStamina + (DeltaValue * Amount);

			OnStaminaAttributeChanged.Broadcast(Stamina.GetMinimumValue(), Stamina.GetMaximumValue(), NewStamina);
			break;
		}

	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("Updated %s Attribute: %f"), *UEnum::GetValueAsString(AttributeType), DeltaValue * Amount);
}

void UCharacterManager::UpdatePrimaryAttributes(float DeltaTime)
{
	// Attribute Data Reference
	FCharacterAttribute& AttributeData = CharacterData.GetAttributeData();
	auto& HealthModule	= AttributeData.GetHealthAttributeModule();
	auto& EnergyModule	= AttributeData.GetEnergyAttributeModule();
	auto& ShieldModule	= AttributeData.GetShieldAttributeModule();
	auto& StaminaModule = AttributeData.GetStaminaAttributeModule();

	// Regenerate Health
	if (HealthModule.IsUpdateEnabled())
	{
		UpdatePrimaryAttributeCurrentValueByType(EPrimaryAttributeType::Health,DeltaTime, HealthModule.GetRegenerateValue());
	}

	// Regenerate Energy
	if(EnergyModule.IsUpdateEnabled())
	{
		UpdatePrimaryAttributeCurrentValueByType(EPrimaryAttributeType::Energy, DeltaTime, EnergyModule.GetRegenerateValue());
	}

	// Regenerate Shield
	if(ShieldModule.IsUpdateEnabled())
	{
		UpdatePrimaryAttributeCurrentValueByType(EPrimaryAttributeType::Shield, DeltaTime, ShieldModule.GetRegenerateValue());
	}

	// Regenerate Stamina
	if(StaminaModule.IsUpdateEnabled())
	{
		UpdatePrimaryAttributeCurrentValueByType(EPrimaryAttributeType::Stamina, DeltaTime, StaminaModule.GetRegenerateValue());
	}
}

#pragma endregion

#pragma region Ability

FCharacterAbilityModule UCharacterManager::GetCharacterAbilityModuleByType(ECharacterAbilityType AbilityType)
{
	return CharacterData.GetAbilityData().FindCharacterAbilityByType(AbilityType);
}

FString UCharacterManager::GetCharacterAbilityTitleByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetTitle();
}

FString UCharacterManager::GetCharacterAbilityDescriptionByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);
	return AbilityModule->GetDescription();
}

ECharacterAbilityType UCharacterManager::GetAbilityTypeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);
	return AbilityModule->GetAbilityType();
}

FVector2D UCharacterManager::GetAbilityPowerRangeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);
	return AbilityModule->GetPowerRange();
}

FVector2D UCharacterManager::GetAbilityDurationRangeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);
	return AbilityModule->GetDurationRange();
}

FVector2D UCharacterManager::GetAbilityCooldownTimeRangeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetCooldownTimeRange();
}

EAbilityCostType UCharacterManager::GetAbilityCostTypeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetCostType();
}

FVector2D UCharacterManager::GetAbilityCostRangeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetCostRange();
}

float UCharacterManager::GetAbilityRangeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetRange();
}

float UCharacterManager::GetAbilityAreaRadiusByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetRadius();
}

float UCharacterManager::GetAbilityRandomPowerByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetRandomPower();
}

float UCharacterManager::GetAbilityRandomDurationByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetRandomDuration();
}

float UCharacterManager::GetAbilityRandomCooldownTimeByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetRandomCooldownTime();
}

float UCharacterManager::GetAbilityRandomCostByType(ECharacterAbilityType AbilityType)
{
	const FCharacterAbilityModule* AbilityModule = CharacterData.GetAbilityData().FindCharacterAbilityByTypePtr(AbilityType);

	return AbilityModule->GetRandomCost();
}

void UCharacterManager::SetCharacterAbilityTitleByType(ECharacterAbilityType AbilityType, const FString& NewTitle)
{

}

void UCharacterManager::SetCharacterAbilityDescriptionByType(ECharacterAbilityType AbilityType, const FString& NewDescription)
{

}

void UCharacterManager::SetAbilityPowerRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewPowerRange)
{

}

void UCharacterManager::SetAbilityDurationRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewDurationRange)
{

}

void UCharacterManager::SetAbilityCooldownTimeRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewCooldownTimeRange)
{

}

void UCharacterManager::SetAbilityCostRangeByType(ECharacterAbilityType AbilityType, const FVector2D& NewCostRange)
{

}

void UCharacterManager::SetAbilityRangeByType(ECharacterAbilityType AbilityType, float NewRange)
{

}

void UCharacterManager::SetAbilityAreaRadiusByType(ECharacterAbilityType AbilityType, float NewRadius)
{

}

void UCharacterManager::SetCharacterAbilityModuleByType(ECharacterAbilityType AbilityType, const FCharacterAbilityModule& NewAbilityModule)
{

}

#pragma endregion

#pragma region Protection

EProtectionType UCharacterManager::GetProtectionTypeByType(EProtectionType Type)
{
	return CharacterData.GetProtectionData().GetProtectionTypeByType(Type);
}

FString UCharacterManager::GetTitleByType(EProtectionType Type)
{
	return CharacterData.GetProtectionData().GetTitleByType(Type);
}

FString UCharacterManager::GetDescriptionByType(EProtectionType Type)
{
	return CharacterData.GetProtectionData().GetDescriptionByType(Type);
}

float UCharacterManager::GetValueByType(EProtectionType Type)
{
	return CharacterData.GetProtectionData().GetValueByType(Type);
}

float UCharacterManager::GetMultiplierByType(EProtectionType Type)
{
	return CharacterData.GetProtectionData().GetMultiplierByType(Type);
}

float UCharacterManager::GetAmplifierByType(EProtectionType Type)
{
	return CharacterData.GetProtectionData().GetAmplifierByType(Type);
}

float UCharacterManager::GetRandomFinalProtectionByType(EProtectionType Type)
{
	return CharacterData.GetProtectionData().GetNetValueByType(Type);
}


#pragma endregion

#pragma region Level 

FCharacterLevelData& UCharacterManager::GetLevelData()
{

	return CharacterData.GetLevelData();
}

float UCharacterManager::GetCurrentExperience()
{
	return CharacterData.GetLevelData().GetExperience();
}

float UCharacterManager::GetNextLevelExperienceThreshold()
{
	int32 CurrentLevel = CharacterData.GetLevelData().GetLevel();

	return CharacterData.GetLevelData().GetExperienceThreshold()[CurrentLevel];
}

int32 UCharacterManager::GetLevel()
{
	return CharacterData.GetLevelData().GetLevel();
}

int32 UCharacterManager::GetMaxLevel()
{
	return CharacterData.GetLevelData().GetMaxLevel();
}

float UCharacterManager::GetExperienceRewardBonus()
{
	return CharacterData.GetLevelData().GetExperienceRewardBonus();
}

void UCharacterManager::AddExperience(float Amount)
{
	if(Amount <= 0.f)
	{
		return;
	}

	// Current level and max level
	int32 CurrentLevel = CharacterData.GetLevelData().GetLevel();
	const int32 MaxLevel = CharacterData.GetLevelData().GetMaxLevel();

	// Current experience and experience thresholds
	float CurrentExperience = CharacterData.GetLevelData().GetExperience();
	const TArray<float>& ExperienceThresholds = CharacterData.GetLevelData().GetExperienceThreshold();

	// Validate experience thresholds
	if(!ExperienceThresholds.IsValidIndex(CurrentLevel))
	{
		#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("AddExperience: Experience thresholds not properly configured."));
		#endif
		return;
	}

	// Remaining experience to process
	float RemainingExperience = Amount;

	// Loop to handle multiple level-ups if enough experience is provided
	while (RemainingExperience > 0.0f && CurrentLevel < MaxLevel)
	{
		const float RequiredXP = ExperienceThresholds[CurrentLevel];
		const float ExperienceToLevelUp = RequiredXP - CurrentExperience;	

		// Enough XP to level up 
		if (RemainingExperience >= ExperienceToLevelUp)
		{
			RemainingExperience -= ExperienceToLevelUp;
			CurrentExperience = 0.0f;

			LevelUp(); // single level increment
			CurrentLevel = CharacterData.GetLevelData().GetLevel();

			// Max level reached after level up 
			if (CurrentLevel >= MaxLevel)
			{
				CurrentExperience = 0.0f;
				RemainingExperience = 0.0f;
				break;
			}
		}
		else
		{
			// Not enough XP to level up, just add the remaining experience
			CurrentExperience += RemainingExperience;
			RemainingExperience = 0.0f;
		}
	}
}

void UCharacterManager::LevelUp()
{
	// Increment level by 1 if not at max level
	// Get current and max level
	int32 CurrentLevel = CharacterData.GetLevelData().GetLevel();
	int32 MaxLevel = CharacterData.GetLevelData().GetMaxLevel();

	// Level up if not at max level
	if (CurrentLevel < MaxLevel)
	{
		CharacterData.GetLevelData().SetLevel(CurrentLevel + 1);
	}
	else
	{
		#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("LevelUp: Character has reached maximum level already."));
		#endif
	}
}

#pragma endregion

#pragma region Movement 

float UCharacterManager::GetWalkSpeed()
{
	return CharacterData.GetMovementData().GetWalkSpeed();
}

float UCharacterManager::GetDefaultSpeed()
{
	return CharacterData.GetMovementData().GetDefaultSpeed();
}

float UCharacterManager::GetMaximumSpeed()
{
	return CharacterData.GetMovementData().GetMaxSpeed();
}

bool UCharacterManager::IsSprintEnabled()
{
	return CharacterData.GetMovementData().IsSprintEnabled();
}

bool UCharacterManager::IsJumpEnabled()
{
	return CharacterData.GetMovementData().IsJumpEnabled();
}

bool UCharacterManager::IsDoubleJumpEnabled()
{
	return CharacterData.GetMovementData().IsDoubleJumpEnabled();
}

int32 UCharacterManager::GetMaxJumpCount()
{
	return CharacterData.GetMovementData().GetMaxJumpCount();
}

float UCharacterManager::GetJumpHeight()
{
	return CharacterData.GetMovementData().GetJumpHeight();
}

#pragma endregion

#pragma region Damage

void UCharacterManager::ExecuteDamage(ACharacterModule* TargetCharacter, float InstigatorDamage, float TargetProtection)
{
	// Calculate final damage after applying protection
	float DamageAmount = InstigatorDamage;
	float ProtectionAmount = TargetProtection;
	float FinalDamage = FMath::Max(DamageAmount - ProtectionAmount, 0.0f);

	// Get target's current health attributes
	float TargetHealth = TargetCharacter->GetCharacterManager()->GetPrimaryAttributeCurrentValueByType(EPrimaryAttributeType::Health);
	float TargetMinHealth = TargetCharacter->GetCharacterManager()->GetPrimaryAttributeMinimumValueByType(EPrimaryAttributeType::Health);
	float TargetMaxHealth = TargetCharacter->GetCharacterManager()->GetPrimaryAttributeMaximumValueByType(EPrimaryAttributeType::Health);

	// Apply damage to target's health
	float NewHealth = FMath::Clamp(TargetHealth - FinalDamage, TargetMinHealth, TargetMaxHealth);
	TargetCharacter->GetCharacterManager()->SetPrimaryAttributeValueByType(EPrimaryAttributeType::Health, TargetMinHealth, TargetMaxHealth, NewHealth);

	if (GEngine)
	{
		// Debug message to show damage applied
		FString DebugMessage = FString::Printf(TEXT("Damage Applied: %.2f | Target Health: %.2f"), FinalDamage, NewHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
	}
}

#pragma endregion

#pragma region PrimaryAttribute

void UCharacterManager::ExecutePrimaryAttributeRegeneration(ACharacterModule* TargetCharacter, EPrimaryAttributeType Type, float Amount)
{
	if (!TargetCharacter || Amount <= 0.f)
	{
		return;
	}

	RegenTarget = TargetCharacter;
	RegenType = Type;
	RemainingRegenAmount = Amount;

	GetWorld()->GetTimerManager().SetTimer
	(
		PrimaryAttributeRegenerationTimerHandle,
		this,
		&UCharacterManager::HandleExecutePrimaryAttributeRegenerationHandler,
		0.1f,	// tick interval
		true    // looping
	);
}

void UCharacterManager::HandleExecutePrimaryAttributeRegenerationHandler()
{
	if (!RegenTarget || !RegenTarget->GetCharacterManager())
	{
		GetWorld()->GetTimerManager().ClearTimer(PrimaryAttributeRegenerationTimerHandle);
		return;
	}

	UCharacterManager* TargetManager = RegenTarget->GetCharacterManager();

	float CurrentValue = TargetManager->GetPrimaryAttributeCurrentValueByType(RegenType);
	float MinValue = TargetManager->GetPrimaryAttributeMinimumValueByType(RegenType);
	float MaxValue = TargetManager->GetPrimaryAttributeMaximumValueByType(RegenType);

	if (RemainingRegenAmount <= 0.f || CurrentValue >= MaxValue)
	{
		GetWorld()->GetTimerManager().ClearTimer(PrimaryAttributeRegenerationTimerHandle);
		return;
	}

	float RegenPerTick = 1.f;

	// 
	float AppliedAmount = FMath::Min(RegenPerTick, FMath::Min(RemainingRegenAmount, MaxValue - CurrentValue));
	TargetManager->SetPrimaryAttributeValueByType(RegenType, MinValue, MaxValue, CurrentValue + AppliedAmount);

	RemainingRegenAmount -= AppliedAmount;


	if (RemainingRegenAmount <= 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(PrimaryAttributeRegenerationTimerHandle);
		return;
	}
}

#pragma endregion

#pragma endregion
