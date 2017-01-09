#include "UnrealCVPrivate.h"
#include "ModelHandler.h"
#include "UE4CVServer.h"
#include "Paths.h"

template <typename ObjClass>
ObjClass* LoadObjFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
}

UStaticMesh* LoadMeshFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UStaticMesh>(Path);
}

void FModelCommandHandler::RegisterCommands()
{
	FDispatcherDelegate Cmd;
	Cmd = FDispatcherDelegate::CreateRaw(this, &FModelCommandHandler::LoadUAsset);
	CommandDispatcher->BindCommand("vget /load [str]", Cmd, "LoadAsset");

}

FExecStatus FModelCommandHandler::LoadUAsset(const TArray<FString>& Path)
{
	// Async version
	FString PathStr = TEXT("/Game/SM_Barracks_S2");

		UStaticMesh* Mesh;
		Mesh = LoadMeshFromPath(FName(*PathStr));
		FVector NewLocation = FVector(0.f, 0.f, 0.f);
		AStaticMeshActor::StaticClass();
		GEngine->GetWorld();
		AStaticMeshActor* newActor = NULL;
		newActor = FUE4CVServer::Get().GetPawn()->GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), NewLocation, FRotator::ZeroRotator);
		UStaticMeshComponent* NewComp;
		NewComp = NewObject<UStaticMeshComponent>(newActor);
		NewComp->AttachTo(newActor->GetRootComponent());
		NewComp->SetStaticMesh(Mesh);
		NewComp->RegisterComponent();
		return FExecStatus::OK(PathStr);
		// return FExecStatus::InvalidArgument;;


}
