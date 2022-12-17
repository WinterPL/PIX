#include "CommandDictionary.h"

#include "CmdDrawPixel.h"
#include "CmdSetResolution.h"
#include "CmdVarBool.h"
#include "CmdVarFloat.h"
#include "CmdSetColor.h"
#include "CmdBeginDraw.h"
#include "CmdEndDraw.h"
#include "CmdVertex.h"
#include "CmdSetFillMode.h"
#include "CmdSetViewport.h"
#include "CmdShowViewport.h"
#include "CmdSetClipping.h"
#include "CmdPushTranslation.h"
#include "CmdPushRotationX.h"
#include "CmdPushRotationY.h"
#include "CmdPushRotationZ.h"
#include "CmdPushScaling.h"
#include "CmdPopMatrix.h"
#include "CmdSetCameraDirection.h"
#include "CmdSetCameraNear.h"
#include "CmdSetCameraFar.h"
#include "CmdSetCameraFov.h"
#include "CmdSetCameraPosition.h"
#include "CmdEnableDepth.h"
#include "CmdSetCullMode.h"
#include "CmdLights.h"
#include "CmdModel.h"
#include "CmdSetShadeMode.h"
#include "CmdSetCorrectUV.h"
#include "CmdSetAddressMode.h"
#include "CmdSetTexture.h"
#include "CmdRayTracer.h"

CommandDictionary* CommandDictionary::Get()
{
	static CommandDictionary sInstance;
	return &sInstance;
}

CommandDictionary::CommandDictionary()
{
	// Initialize dictionary

	// Setting commands
	RegisterCommand<CmdSetResolution>();

	// Variable commands
	RegisterCommand<CmdVarBool>();
	RegisterCommand<CmdVarFloat>();

	// Camera commands
	RegisterCommand<CmdSetCameraDirection>();
	RegisterCommand<CmdSetCameraPosition>();

	// Depth buffer commands
	RegisterCommand<CmdEnableDepth>();

	// Light commands
	RegisterCommand<CmdSetLightAmbient>();
	RegisterCommand<CmdSetLightDiffuse>();
	RegisterCommand<CmdSetLightSpecular>();
	RegisterCommand<CmdAddDirectionalLight>();
	RegisterCommand<CmdAddPointLight>();
	RegisterCommand<CmdAddSpotLight>();

	// Matrix commands
	RegisterCommand<CmdPopMatrix>();
	RegisterCommand<CmdPushRotationX>();
	RegisterCommand<CmdPushRotationY>();
	RegisterCommand<CmdPushRotationZ>();
	RegisterCommand<CmdPushScaling>();
	RegisterCommand<CmdPushTranslation>();

	// Primitive commands
	RegisterCommand<CmdSetCullMode>();
	RegisterCommand<CmdBeginDraw>();
	RegisterCommand<CmdEndDraw>();
	RegisterCommand<CmdVertex>();
	RegisterCommand<CmdModel>();

	// Rasterization commands
	RegisterCommand<CmdSetColor>();
	RegisterCommand<CmdSetFillMode>();
	RegisterCommand<CmdDrawPixel>();

	// Texture commands
	RegisterCommand<CmdSetAddressMode>();
	RegisterCommand<CmdSetCorrectUV>();
	RegisterCommand<CmdSetTexture>();

	// Viewport commands
	RegisterCommand<CmdSetClipping>();
	RegisterCommand<CmdSetViewport>();
	RegisterCommand<CmdShowViewport>();

	// Ray Tracing commands
	RegisterCommand<CmdBeginRayTracing>();
	RegisterCommand<CmdEndRayTracing>();
	RegisterCommand<CmdRTSphere>();
	RegisterCommand<CmdRTLight>();
}

TextEditor::LanguageDefinition CommandDictionary::GenerateLanguageDefinition()
{
	TextEditor::LanguageDefinition langDef;

	langDef.mName = "Pix";

	langDef.mKeywords.insert("var");

	for (auto&[keyword, command] : mCommandMap)
	{
		TextEditor::Identifier id;
		id.mDeclaration = command->GetDescription();
		langDef.mIdentifiers.insert(std::make_pair(keyword, id));
	}

	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\$[a-zA-Z_]+", TextEditor::PaletteIndex::Keyword));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", TextEditor::PaletteIndex::String));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\'\\\\?[^\\']\\'", TextEditor::PaletteIndex::CharLiteral));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", TextEditor::PaletteIndex::Number));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", TextEditor::PaletteIndex::Punctuation));

	langDef.mCommentStart = "/*";
	langDef.mCommentEnd = "*/";
	langDef.mSingleLineComment = "//";

	langDef.mAutoIndentation = true;
	langDef.mCaseSensitive = true;

	return langDef;
}

Command* CommandDictionary::CommandLookup(const std::string& keyword)
{
	auto iter = mCommandMap.find(keyword);
	if (iter == mCommandMap.end())
		return nullptr;
	return iter->second.get();
}

template <class T>
void CommandDictionary::RegisterCommand()
{
	static_assert(std::is_base_of_v<Command, T>, "Invalid command type.");
	auto newCommand = std::make_unique<T>();
	mCommandMap.emplace(newCommand->GetName(), std::move(newCommand));
}