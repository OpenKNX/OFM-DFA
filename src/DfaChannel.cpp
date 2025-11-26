// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2023-2025 Cornelius Koepp

#include "DfaChannel.h"

#if (DFA_DEF_STATES_COUNT == 16)
    // ok
#elif (DFA_DEF_STATES_COUNT == 32)
    // ok
#else
    #error "illegal DFA_DEF_STATES_COUNT!"
#endif

#pragma region "DFA_CHANNEL_ADDR"

const uint8_t DfaChannel::_inputKo[DFA_DEF_INPUTS_COUNT] = {
    DFA_KoKOaInput1,
    DFA_KoKOaInput2,
    DFA_KoKOaInput3,
    DFA_KoKOaInput4,
    DFA_KoKOaInput5,
    DFA_KoKOaInput6,
    DFA_KoKOaInput7,
    DFA_KoKOaInput8,
};
// Value of DFA_KoKOaInput[1-8] by 0-based index
#define DFA_KoKOaInput__N__(IDX) DFA_KoKOaInput1 + IDX * (DFA_KoKOaInput2 - DFA_KoKOaInput1)
// Value of DFA_KoCalcNumber(DFA_KoKOaInput[1-8]) by 0-based index
#define DFA_Channel_Input_KO(IDX) DFA_KoCalcNumber(DFA_KoKOaInput__N__(IDX))

// TODO calculate index; expected distance should be protected by compile error
const uint16_t DfaChannel::_inputConfPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aSymbolAInput,
    DFA_aSymbolBInput,
    DFA_aSymbolCInput,
    DFA_aSymbolDInput,
    DFA_aSymbolEInput,
    DFA_aSymbolFInput,
    DFA_aSymbolGInput,
    DFA_aSymbolHInput,
};
// Value of DFA_aInputSymbol[1-8]Ko by 0-based index
#define DFA_aSymbol__N__Ko(IDX) DFA_aSymbolAInput + IDX * (DFA_aSymbolBInput - DFA_aSymbolAInput)
//     const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[input])) & DFA_aSymbolAInputMask) >> DFA_aSymbolAInputShift);
#define DFA_Channel_Input_Config(IDX) ((knx.paramByte(DFA_aSymbol__N__Ko(IDX)) & DFA_aSymbolAInputMask) >> DFA_aSymbolAInputShift)


#if DFA_aSymbolALogicNumber != DFA_aSymbolAKoNumber
    #error "DFA_aSymbolALogicNumber != DFA_aSymbolAKoNumber"
#endif
const uint16_t DfaChannel::_inputConfNumberPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aSymbolAKoNumber,
    DFA_aSymbolBKoNumber,
    DFA_aSymbolCKoNumber,
    DFA_aSymbolDKoNumber,
    DFA_aSymbolEKoNumber,
    DFA_aSymbolFKoNumber,
    DFA_aSymbolGKoNumber,
    DFA_aSymbolHKoNumber,
};
const uint16_t DfaChannel::_inputTriggerPRI[DFA_DEF_INPUTS_COUNT] = {
    DFA_aSymbolATrigger,
    DFA_aSymbolBTrigger,
    DFA_aSymbolCTrigger,
    DFA_aSymbolDTrigger,
    DFA_aSymbolETrigger,
    DFA_aSymbolFTrigger,
    DFA_aSymbolGTrigger,
    DFA_aSymbolHTrigger,
};


// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for next state by current state and input

// Value of DFA_KoKOaInput[1-8] by 0-based index
#define DFA_aTransfer_State__N__Input__M__(N, M) DFA_ad01A + N * (DFA_ad02A - DFA_ad01A) + M * (DFA_ad01B - DFA_ad01A)
// Value of DFA_KoCalcNumber(DFA_KoKOaInput[1-8]) by 0-based index
#define DFA_Channel_TransferByStateInput(STATE_IDX, IN_IDX) DFA_KoCalcNumber(DFA_aTransfer_State__N__Input__M__(STATE_IDX, IN_IDX))


const uint16_t DfaChannel::_transPRI[DFA_DEF_STATES_COUNT][DFA_DEF_INPUTS_WITH_T_COUNT] = {
    {DFA_ad01A, DFA_ad01B, DFA_ad01C, DFA_ad01D, DFA_ad01E, DFA_ad01F, DFA_ad01G, DFA_ad01H, DFA_ad01T},
    {DFA_ad02A, DFA_ad02B, DFA_ad02C, DFA_ad02D, DFA_ad02E, DFA_ad02F, DFA_ad02G, DFA_ad02H, DFA_ad02T},
    {DFA_ad03A, DFA_ad03B, DFA_ad03C, DFA_ad03D, DFA_ad03E, DFA_ad03F, DFA_ad03G, DFA_ad03H, DFA_ad03T},
    {DFA_ad04A, DFA_ad04B, DFA_ad04C, DFA_ad04D, DFA_ad04E, DFA_ad04F, DFA_ad04G, DFA_ad04H, DFA_ad04T},
    {DFA_ad05A, DFA_ad05B, DFA_ad05C, DFA_ad05D, DFA_ad05E, DFA_ad05F, DFA_ad05G, DFA_ad05H, DFA_ad05T},
    {DFA_ad06A, DFA_ad06B, DFA_ad06C, DFA_ad06D, DFA_ad06E, DFA_ad06F, DFA_ad06G, DFA_ad06H, DFA_ad06T},
    {DFA_ad07A, DFA_ad07B, DFA_ad07C, DFA_ad07D, DFA_ad07E, DFA_ad07F, DFA_ad07G, DFA_ad07H, DFA_ad07T},
    {DFA_ad08A, DFA_ad08B, DFA_ad08C, DFA_ad08D, DFA_ad08E, DFA_ad08F, DFA_ad08G, DFA_ad08H, DFA_ad08T},
    {DFA_ad09A, DFA_ad09B, DFA_ad09C, DFA_ad09D, DFA_ad09E, DFA_ad09F, DFA_ad09G, DFA_ad09H, DFA_ad09T},
    {DFA_ad10A, DFA_ad10B, DFA_ad10C, DFA_ad10D, DFA_ad10E, DFA_ad10F, DFA_ad10G, DFA_ad10H, DFA_ad10T},
    {DFA_ad11A, DFA_ad11B, DFA_ad11C, DFA_ad11D, DFA_ad11E, DFA_ad11F, DFA_ad11G, DFA_ad11H, DFA_ad11T},
    {DFA_ad12A, DFA_ad12B, DFA_ad12C, DFA_ad12D, DFA_ad12E, DFA_ad12F, DFA_ad12G, DFA_ad12H, DFA_ad12T},
    {DFA_ad13A, DFA_ad13B, DFA_ad13C, DFA_ad13D, DFA_ad13E, DFA_ad13F, DFA_ad13G, DFA_ad13H, DFA_ad13T},
    {DFA_ad14A, DFA_ad14B, DFA_ad14C, DFA_ad14D, DFA_ad14E, DFA_ad14F, DFA_ad14G, DFA_ad14H, DFA_ad14T},
    {DFA_ad15A, DFA_ad15B, DFA_ad15C, DFA_ad15D, DFA_ad15E, DFA_ad15F, DFA_ad15G, DFA_ad15H, DFA_ad15T},
    {DFA_ad16A, DFA_ad16B, DFA_ad16C, DFA_ad16D, DFA_ad16E, DFA_ad16F, DFA_ad16G, DFA_ad16H, DFA_ad16T},
#if DFA_DEF_STATES_COUNT > 16
    {DFA_ad17A, DFA_ad17B, DFA_ad17C, DFA_ad17D, DFA_ad17E, DFA_ad17F, DFA_ad17G, DFA_ad17H, DFA_ad17T},
    {DFA_ad18A, DFA_ad18B, DFA_ad18C, DFA_ad18D, DFA_ad18E, DFA_ad18F, DFA_ad18G, DFA_ad18H, DFA_ad18T},
    {DFA_ad19A, DFA_ad19B, DFA_ad19C, DFA_ad19D, DFA_ad19E, DFA_ad19F, DFA_ad19G, DFA_ad19H, DFA_ad19T},
    {DFA_ad20A, DFA_ad20B, DFA_ad20C, DFA_ad20D, DFA_ad20E, DFA_ad20F, DFA_ad20G, DFA_ad20H, DFA_ad20T},
    {DFA_ad21A, DFA_ad21B, DFA_ad21C, DFA_ad21D, DFA_ad21E, DFA_ad21F, DFA_ad21G, DFA_ad21H, DFA_ad21T},
    {DFA_ad22A, DFA_ad22B, DFA_ad22C, DFA_ad22D, DFA_ad22E, DFA_ad22F, DFA_ad22G, DFA_ad22H, DFA_ad22T},
    {DFA_ad23A, DFA_ad23B, DFA_ad23C, DFA_ad23D, DFA_ad23E, DFA_ad23F, DFA_ad23G, DFA_ad23H, DFA_ad23T},
    {DFA_ad24A, DFA_ad24B, DFA_ad24C, DFA_ad24D, DFA_ad24E, DFA_ad24F, DFA_ad24G, DFA_ad24H, DFA_ad24T},
    {DFA_ad25A, DFA_ad25B, DFA_ad25C, DFA_ad25D, DFA_ad25E, DFA_ad25F, DFA_ad25G, DFA_ad25H, DFA_ad25T},
    {DFA_ad26A, DFA_ad26B, DFA_ad26C, DFA_ad26D, DFA_ad26E, DFA_ad26F, DFA_ad26G, DFA_ad26H, DFA_ad26T},
    {DFA_ad27A, DFA_ad27B, DFA_ad27C, DFA_ad27D, DFA_ad27E, DFA_ad27F, DFA_ad27G, DFA_ad27H, DFA_ad27T},
    {DFA_ad28A, DFA_ad28B, DFA_ad28C, DFA_ad28D, DFA_ad28E, DFA_ad28F, DFA_ad28G, DFA_ad28H, DFA_ad28T},
    {DFA_ad29A, DFA_ad29B, DFA_ad29C, DFA_ad29D, DFA_ad29E, DFA_ad29F, DFA_ad29G, DFA_ad29H, DFA_ad29T},
    {DFA_ad30A, DFA_ad30B, DFA_ad30C, DFA_ad30D, DFA_ad30E, DFA_ad30F, DFA_ad30G, DFA_ad30H, DFA_ad30T},
    {DFA_ad31A, DFA_ad31B, DFA_ad31C, DFA_ad31D, DFA_ad31E, DFA_ad31F, DFA_ad31G, DFA_ad31H, DFA_ad31T},
    {DFA_ad32A, DFA_ad32B, DFA_ad32C, DFA_ad32D, DFA_ad32E, DFA_ad32F, DFA_ad32G, DFA_ad32H, DFA_ad32T},
#endif
#if DFA_DEF_STATES_COUNT > 32
    {DFA_ad33A, DFA_ad33B, DFA_ad33C, DFA_ad33D, DFA_ad33E, DFA_ad33F, DFA_ad33G, DFA_ad33H, DFA_ad33T},
    {DFA_ad34A, DFA_ad34B, DFA_ad34C, DFA_ad34D, DFA_ad34E, DFA_ad34F, DFA_ad34G, DFA_ad34H, DFA_ad34T},
    {DFA_ad35A, DFA_ad35B, DFA_ad35C, DFA_ad35D, DFA_ad35E, DFA_ad35F, DFA_ad35G, DFA_ad35H, DFA_ad35T},
    {DFA_ad36A, DFA_ad36B, DFA_ad36C, DFA_ad36D, DFA_ad36E, DFA_ad36F, DFA_ad36G, DFA_ad36H, DFA_ad36T},
    {DFA_ad37A, DFA_ad37B, DFA_ad37C, DFA_ad37D, DFA_ad37E, DFA_ad37F, DFA_ad37G, DFA_ad37H, DFA_ad37T},
    {DFA_ad38A, DFA_ad38B, DFA_ad38C, DFA_ad38D, DFA_ad38E, DFA_ad38F, DFA_ad38G, DFA_ad38H, DFA_ad38T},
    {DFA_ad39A, DFA_ad39B, DFA_ad39C, DFA_ad39D, DFA_ad39E, DFA_ad39F, DFA_ad39G, DFA_ad39H, DFA_ad39T},
    {DFA_ad40A, DFA_ad40B, DFA_ad40C, DFA_ad40D, DFA_ad40E, DFA_ad40F, DFA_ad40G, DFA_ad40H, DFA_ad40T},
    {DFA_ad41A, DFA_ad41B, DFA_ad41C, DFA_ad41D, DFA_ad41E, DFA_ad41F, DFA_ad41G, DFA_ad41H, DFA_ad41T},
    {DFA_ad42A, DFA_ad42B, DFA_ad42C, DFA_ad42D, DFA_ad42E, DFA_ad42F, DFA_ad42G, DFA_ad42H, DFA_ad42T},
    {DFA_ad43A, DFA_ad43B, DFA_ad43C, DFA_ad43D, DFA_ad43E, DFA_ad43F, DFA_ad43G, DFA_ad43H, DFA_ad43T},
    {DFA_ad44A, DFA_ad44B, DFA_ad44C, DFA_ad44D, DFA_ad44E, DFA_ad44F, DFA_ad44G, DFA_ad44H, DFA_ad44T},
    {DFA_ad45A, DFA_ad45B, DFA_ad45C, DFA_ad45D, DFA_ad45E, DFA_ad45F, DFA_ad45G, DFA_ad45H, DFA_ad45T},
    {DFA_ad46A, DFA_ad46B, DFA_ad46C, DFA_ad46D, DFA_ad46E, DFA_ad46F, DFA_ad46G, DFA_ad46H, DFA_ad46T},
    {DFA_ad47A, DFA_ad47B, DFA_ad47C, DFA_ad47D, DFA_ad47E, DFA_ad47F, DFA_ad47G, DFA_ad47H, DFA_ad47T},
    {DFA_ad48A, DFA_ad48B, DFA_ad48C, DFA_ad48D, DFA_ad48E, DFA_ad48F, DFA_ad48G, DFA_ad48H, DFA_ad48T},
    {DFA_ad49A, DFA_ad49B, DFA_ad49C, DFA_ad49D, DFA_ad49E, DFA_ad49F, DFA_ad49G, DFA_ad49H, DFA_ad49T},
    {DFA_ad50A, DFA_ad50B, DFA_ad50C, DFA_ad50D, DFA_ad50E, DFA_ad50F, DFA_ad50G, DFA_ad50H, DFA_ad50T},
    {DFA_ad51A, DFA_ad51B, DFA_ad51C, DFA_ad51D, DFA_ad51E, DFA_ad51F, DFA_ad51G, DFA_ad51H, DFA_ad51T},
    {DFA_ad52A, DFA_ad52B, DFA_ad52C, DFA_ad52D, DFA_ad52E, DFA_ad52F, DFA_ad52G, DFA_ad52H, DFA_ad52T},
    {DFA_ad53A, DFA_ad53B, DFA_ad53C, DFA_ad53D, DFA_ad53E, DFA_ad53F, DFA_ad53G, DFA_ad53H, DFA_ad53T},
    {DFA_ad54A, DFA_ad54B, DFA_ad54C, DFA_ad54D, DFA_ad54E, DFA_ad54F, DFA_ad54G, DFA_ad54H, DFA_ad54T},
    {DFA_ad55A, DFA_ad55B, DFA_ad55C, DFA_ad55D, DFA_ad55E, DFA_ad55F, DFA_ad55G, DFA_ad55H, DFA_ad55T},
    {DFA_ad56A, DFA_ad56B, DFA_ad56C, DFA_ad56D, DFA_ad56E, DFA_ad56F, DFA_ad56G, DFA_ad56H, DFA_ad56T},
    {DFA_ad57A, DFA_ad57B, DFA_ad57C, DFA_ad57D, DFA_ad57E, DFA_ad57F, DFA_ad57G, DFA_ad57H, DFA_ad57T},
    {DFA_ad58A, DFA_ad58B, DFA_ad58C, DFA_ad58D, DFA_ad58E, DFA_ad58F, DFA_ad58G, DFA_ad58H, DFA_ad58T},
    {DFA_ad59A, DFA_ad59B, DFA_ad59C, DFA_ad59D, DFA_ad59E, DFA_ad59F, DFA_ad59G, DFA_ad59H, DFA_ad59T},
    {DFA_ad60A, DFA_ad60B, DFA_ad60C, DFA_ad60D, DFA_ad60E, DFA_ad60F, DFA_ad60G, DFA_ad60H, DFA_ad60T},
    {DFA_ad61A, DFA_ad61B, DFA_ad61C, DFA_ad61D, DFA_ad61E, DFA_ad61F, DFA_ad61G, DFA_ad61H, DFA_ad61T},
    {DFA_ad62A, DFA_ad62B, DFA_ad62C, DFA_ad62D, DFA_ad62E, DFA_ad62F, DFA_ad62G, DFA_ad62H, DFA_ad62T},
    {DFA_ad63A, DFA_ad63B, DFA_ad63C, DFA_ad63D, DFA_ad63E, DFA_ad63F, DFA_ad63G, DFA_ad63H, DFA_ad63T},
    {DFA_ad64A, DFA_ad64B, DFA_ad64C, DFA_ad64D, DFA_ad64E, DFA_ad64F, DFA_ad64G, DFA_ad64H, DFA_ad64T},
#endif
};

// TODO calculate index; expected distance should be protected by compile error
// Define (relative) parameter address-index for timeout duration and timeout state
const uint16_t DfaChannel::_timeoutPRI[DFA_DEF_STATES_COUNT] = {
    {DFA_ad01TTime},
    {DFA_ad02TTime},
    {DFA_ad03TTime},
    {DFA_ad04TTime},
    {DFA_ad05TTime},
    {DFA_ad06TTime},
    {DFA_ad07TTime},
    {DFA_ad08TTime},
    {DFA_ad09TTime},
    {DFA_ad10TTime},
    {DFA_ad11TTime},
    {DFA_ad12TTime},
    {DFA_ad13TTime},
    {DFA_ad14TTime},
    {DFA_ad15TTime},
    {DFA_ad16TTime},
#if DFA_DEF_STATES_COUNT > 16
    {DFA_ad17TTime},
    {DFA_ad18TTime},
    {DFA_ad19TTime},
    {DFA_ad20TTime},
    {DFA_ad21TTime},
    {DFA_ad22TTime},
    {DFA_ad23TTime},
    {DFA_ad24TTime},
    {DFA_ad25TTime},
    {DFA_ad26TTime},
    {DFA_ad27TTime},
    {DFA_ad28TTime},
    {DFA_ad29TTime},
    {DFA_ad30TTime},
    {DFA_ad31TTime},
    {DFA_ad32TTime},
#endif
#if DFA_DEF_STATES_COUNT > 32
    {DFA_ad33TTime},
    {DFA_ad34TTime},
    {DFA_ad35TTime},
    {DFA_ad36TTime},
    {DFA_ad37TTime},
    {DFA_ad38TTime},
    {DFA_ad39TTime},
    {DFA_ad40TTime},
    {DFA_ad41TTime},
    {DFA_ad42TTime},
    {DFA_ad43TTime},
    {DFA_ad44TTime},
    {DFA_ad45TTime},
    {DFA_ad46TTime},
    {DFA_ad47TTime},
    {DFA_ad48TTime},
    {DFA_ad49TTime},
    {DFA_ad50TTime},
    {DFA_ad51TTime},
    {DFA_ad52TTime},
    {DFA_ad53TTime},
    {DFA_ad54TTime},
    {DFA_ad55TTime},
    {DFA_ad56TTime},
    {DFA_ad57TTime},
    {DFA_ad58TTime},
    {DFA_ad59TTime},
    {DFA_ad60TTime},
    {DFA_ad61TTime},
    {DFA_ad62TTime},
    {DFA_ad63TTime},
    {DFA_ad64TTime},
#endif
};

#pragma endregion "DFA_CHANNEL_ADDR"

#pragma region "DFA_CHANNEL_BASE"

DfaChannel::DfaChannel(uint8_t index)
{
    _channelIndex = index;
    for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
    {
        _outputs[i] = new DfaOutput(_channelIndex, i);
    }
}

const std::string DfaChannel::name()
{
    return "DFA-Channel";
}

#pragma endregion "DFA_CHANNEL_BASE"

void DfaChannel::setup()
{
    _channelActive = (ParamDFA_aActive == 0b01);
    logDebugP("setup (act=%d dly=%ds run=%d)", _channelActive, ParamDFA_aStartupDelayTimeMS / 1000, ParamDFA_aStartPause != 2);

    if (_channelActive)
    {
        initInputConfig();

        // TODO QS: check first state handling, especially sending
        _firstState = ParamDFA_az0 - 1;
        // _firstStateTimeoutDelay_ms = getStateTimeoutDelay_ms(_firstState);

        // could be overwritten in restore
        _firstRunning = (ParamDFA_aStartPause != 2);

        // actual starting in processAfterStartupDelay() ...
    }
}

#pragma region "DFA_CHANNEL_INPUT_INIT"

#if (DFA_aSymbolBInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolBInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolBTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolBInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol B and A"
#endif
#if (DFA_aSymbolCInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolCInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolCTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolCInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol C and A"
#endif
#if (DFA_aSymbolDInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolDInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolDTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolDInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol D and A"
#endif
#if (DFA_aSymbolEInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolEInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolETriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolEInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol E and A"
#endif
#if (DFA_aSymbolFInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolFInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolFTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolFInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol F and A"
#endif
#if (DFA_aSymbolGInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolGInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolGTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolGInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol G and A"
#endif
#if (DFA_aSymbolHInputMask != DFA_aSymbolAInputMask) || (DFA_aSymbolHInputShift != DFA_aSymbolAInputShift) || (DFA_aSymbolHTriggerMask != DFA_aSymbolAInputMask) || (DFA_aSymbolHInputShift != DFA_aSymbolATriggerShift)
    #error "Symbol{Input,Trigger}{Mask,Shift} mismatch for Symbol H and A"
#endif
#define DFA_aSymbol___InputMask DFA_aSymbolAInputMask
#define DFA_aSymbol___InputShift DFA_aSymbolAInputShift
#define DFA_aSymbol___TriggerMask DFA_aSymbolATriggerMask
#define DFA_aSymbol___TriggerShift DFA_aSymbolATriggerShift

uint16_t DfaChannel::getLogicOutputKoNumber(const uint8_t /* intended overlapping name for usage in macro! */ _channelIndex)
{
    return LOG_KoCalcNumber(LOG_KoKOfO);
}

uint16_t DfaChannel::getInputKoNumber(const uint8_t input)
{
    // TODO ensure position of T
    const uint8_t inputConf = ((knx.paramByte(DFA_ParamCalcIndex(_inputConfPRI[input])) & DFA_aSymbol___InputMask) >> DFA_aSymbol___InputShift);
    // logDebugP("  get ko for input=%i -> conf=%i", input, inputConf);
    switch (inputConf)
    {
        case 1: // Own KO
            return DFA_KoCalcNumber(_inputKo[input]);
        case 3: // Logic-Output (KO)
            {
                // TODO optimize/use API for this
                const u_int16_t logicNumber = knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[input]));
                if (logicNumber > LOG_ChannelCount || logicNumber > 99)
                {
                    logErrorP("Invalid LOG-channel %u for input %u", logicNumber, input);
                    return 0;
                }
                return getLogicOutputKoNumber(logicNumber - 1);
            }
        case 2: // Existing KO
            return knx.paramWord(DFA_ParamCalcIndex(_inputConfNumberPRI[input]));
    }
    // default, including case 0 (disabled)
    return 0;
}

void DfaChannel::initNonPairedInput(const uint8_t i)
{
    const uint16_t koNumber = getInputKoNumber(i);
    _inputs[i].koNumber = koNumber;
    _inputs[i].trigger = (koNumber > 0) ? static_cast<DfaInputTrigger>((knx.paramByte(DFA_ParamCalcIndex(_inputTriggerPRI[i])) & DFA_aSymbol___TriggerMask) >> DFA_aSymbol___TriggerShift) : DfaInputTrigger::disabled;
    logDebugP("  separate: %d ko=%i trigger=%i", i, koNumber, _inputs[i].trigger);
}

void DfaChannel::initInputConfig()
{
    // inputs for symbols A..H (can be defined in pairs A/B, C/D, E/F, G/H)
    const bool combined[DFA_DEF_INPUTS_COUNT / 2] = {ParamDFA_aSymbolPairAB, ParamDFA_aSymbolPairCD, ParamDFA_aSymbolPairEF, ParamDFA_aSymbolPairGH};
    for (uint8_t iPair = 0; iPair < DFA_DEF_INPUTS_COUNT / 2; iPair++)
    {
        const uint8_t iFirst = iPair * 2;
        const uint8_t iSecond = iFirst + 1;
        logDebugP("input-pair %d, first=%d, second=%d; ispair=%d", iPair, iFirst, iSecond, combined[iPair]);
        if (combined[iPair])
        {
            // one shared input for 2 symbols
            const uint16_t koNumber = getInputKoNumber(iFirst);

            _inputs[iFirst].koNumber = koNumber;
            _inputs[iFirst].trigger = (koNumber > 0) ? DfaInputTrigger::only1 : DfaInputTrigger::disabled;
            _inputs[iSecond].koNumber = koNumber;
            _inputs[iSecond].trigger = (koNumber > 0) ? DfaInputTrigger::only0 : DfaInputTrigger::disabled;
        }
        else
        {
            // separate input for 2 symbols
            initNonPairedInput(iFirst);
            initNonPairedInput(iSecond);
        }
    }

    // input for symbol T (not part of a pair)
    initNonPairedInput(DFA_INPUT_SYMBOL_T);

#ifdef OPENKNX_DEBUG
    for (size_t i = 0; i < DFA_DEF_INPUTS_WITH_T_COUNT; i++)
    {
        logDebugP("input[%d]: ko=%d trigger=%d", i, _inputs[i].koNumber, _inputs[i].trigger);
    }
#endif
}

#pragma endregion "DFA_CHANNEL_INPUT_INIT"

void DfaChannel::processAfterStartupDelay()
{
    // start after device global delay
    if (_channelActive)
    {
        logDebugP("processAfterStartupDelay");
        _processStartup = true;
        _startupDelayBegin_ms = millis();
    }
}

void DfaChannel::loop()
{
    // !_channelActive will result in _running=false, so no need for checking
    if (_running)
    {
        if (_stateTimeoutDelay_ms > 0 && delayCheckMillis(_stateTimeoutBegin_ms, _stateTimeoutDelay_ms))
        {
            // prio 1: timeout of state => transfer to following state

            // logDebugP("timeout reached (@%d+%dms >=%d)", _stateTimeoutBegin_ms, _stateTimeoutDelay_ms, millis());
            transfer(DFA_INPUT_SYMBOL_T);
        }
        else
        {
            // prio 2: cyclic sending of outputs
            for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
            {
                _outputs[i]->loop();
            }
        }
    }
    else if (_processStartup && delayCheckMillis(_startupDelayBegin_ms, ParamDFA_aStartupDelayTimeMS))
    {
        _processStartup = false;

        // set to running. This includes setting the start state
        setRunning(_firstRunning, true);
    }
}

void DfaChannel::processInputKo(GroupObject &ko)
{
    if (!_channelActive)
        return; // ignore inactive channel

    // TODO optimize check of ko-Number

    const uint16_t koNumber = ko.asap();

    // TODO define behaviour within startup delay!
    if (koNumber == DFA_KoCalcNumber(DFA_KoKOaRunSet))
    {
        logDebugP("processInputKo set running");
        setRunning(ko.value(DPT_Start));
    }
    // TODO define expected behaviour when changed before; will be relevant for inputs by KO-Index
    if (_running)
    {
        if (koNumber == DFA_KoCalcNumber(DFA_KoKOaStateI))
        {
            // input only for visible KO, so no need to check:
            // .. && ParamDFA_aStateSetting==0b01
            logDebugP("processInputKo set state (separate); StateSetting=%d, ..Same=%d", ParamDFA_aStateSetting, ParamDFA_aStateSettingSame);
            setState(ko.value(DPT_SceneNumber), static_cast<DfaDirectSetSame>(ParamDFA_aStateSettingSame));
            // TODO check updating history
        }
        else if (koNumber == DFA_KoCalcNumber(DFA_KoKOaState) && ParamDFA_aStateSetting == 0b10)
        {
            logDebugP("processInputKo set state (combined); StateSetting=%d, ..Same=%d", ParamDFA_aStateSetting, ParamDFA_aStateSettingSame);

            // ignore same state to prevent processing the result of own sending to shared K
            setState(ko.value(DPT_SceneNumber), DfaDirectSetSame::ignore);
            // TODO check updating history

            // ensure KO has the value of current state!
            // TODO restore KO value for invalid state only
            ko.valueNoSend(_state, DPT_SceneNumber);
        }
        else if (ko.valueSize() == 1) // TODO check if adequate, or add support for other input types
        {
            const bool value = ko.value(DPT_Switch);

            // check (new or existing) inputs based on ko-numbers
            for (size_t i = 0; i < DFA_DEF_INPUTS_WITH_T_COUNT; i++)
            {
                if (koNumber == _inputs[i].koNumber)
                {
                    const bool triggered = static_cast<uint8_t>(_inputs[i].trigger) & (1 << value);
                    logDebugP("processInputKo input=%d (ko=%d; triggered=%d)", i + 1, koNumber, triggered);
                    if (triggered)
                    {
                        transfer(i);
                        break; // only one! // TODO check
                    }
                }
            }
        }
    }
}

void DfaChannel::setRunning(const bool requestRun, const bool first /*= false*/)
{
    bool send = first;
    if (_running != requestRun)
    {
        if (!requestRun)
        {
            // suspend
            logDebugP("suspend");
            _pauseBegin = millis();
        }
        else if (_state == DFA_STATE_UNDEFINED)
        {
            // first activation
            logDebugP("first activation");
            setState(_firstState);   // TODO check using transfer(..)
            addHistory(249, _state); // TODO define constant

            logDebugP("restore: _stateTimeoutDelay_ms=%d ParamDFA_aStateRestore=%d _firstStateTimeoutDelay_ms=%d ParamDFA_aChannelDelayTimeMS=%d", _stateTimeoutDelay_ms, ParamDFA_aStateRestore, _firstStateTimeoutDelay_ms, ParamDFA_aStartupDelayTimeMS);
            // TODO check usage of _firstStateTimeoutDelay_ms, this is the remaining delay and should be renamed
            // _stateTimeoutDelay_ms is set to current's state timeout in setState(..)
            if (_stateTimeoutDelay_ms > 0 && (ParamDFA_aStateRestore & 0b10) && _firstStateTimeoutDelay_ms > 0)
            {
                // remaining timeout starts with device;
                // this will already add an unknown delay caused by downtime of unknown length,
                // which should be solved by (re)store the absolute timeout end
                if (_firstStateTimeoutDelay_ms > _stateTimeoutBegin_ms)
                {
                    logDebugP("restore with shortened delay");
                    // TODO check/define behaviour when timeout configuration was changed, and is shorter than saved remaining time
                    _stateTimeoutDelay_ms = _firstStateTimeoutDelay_ms - _stateTimeoutBegin_ms;
                }
                else
                {
                    // TODO check direct restore of timeout-state, to reduce sending
                    logDebugP("restore with ended delay");
                    _stateTimeoutDelay_ms = 1;
                }
            }
            // all following state-updates are not part of restore => no special handling
            _restoreOutputs = false;
        }
        else
        {
            // resume & increase delay by pause time
            logDebugP("resume after sleeping %dms", (millis() - _pauseBegin));
            _stateTimeoutBegin_ms += (millis() - _pauseBegin);
        }
        _running = requestRun;
        send = true;
    }

    if (send && (ParamDFA_aStartPause != 0))
        KoDFA_KOaRunning.value(_running, DPT_State);
}

uint32_t DfaChannel::getStateTimeoutDelay_ms(const uint8_t state)
{
    // TODO ensure returning 0 for undefined timeout state
    return paramDelay(knx.paramWord(DFA_ParamCalcIndex(_timeoutPRI[state])));
}

bool DfaChannel::isValidState(const uint8_t state)
{
    return state < DFA_DEF_STATES_COUNT;
}

void DfaChannel::setState(const uint8_t nextState, const DfaDirectSetSame sameStateBehaviour /*= DfaDirectSetSame::timeout_restart*/)
{
    if (isValidState(nextState))
    {
        const bool stateChanged = (_state != nextState);
        if (!stateChanged && sameStateBehaviour == DfaDirectSetSame::ignore)
            return;

        _state = nextState;
        if (stateChanged || sameStateBehaviour == DfaDirectSetSame::timeout_restart)
        {
            // reset timeout
            _stateTimeoutDelay_ms = getStateTimeoutDelay_ms(nextState);
            resetTimeout();
        }

        // send state
        GroupObject *ko = &KoDFA_KOaState;
        if (ko->valueNoSendCompare(_state, DPT_SceneNumber))
            ko->objectWritten();

        // if (_stateTimeoutDelay_ms > 0)
        //     logDebugP("  with timeout state %d after %dms", getTimeoutState(nextState), _stateTimeoutDelay_ms);

        for (uint8_t i = 0; i < DFA_DEF_OUTPUTS_COUNT; i++)
        {
            _outputs[i]->stateUpdate(_state, _restoreOutputs);
        }
    }
}

#pragma region "DFA_CHANNEL_TRANSFER"

/**
 * @brief Transfer the DFA to the next state based on the current state and input symbol.
 * @param input
 *  SYMBOL      : VALUE                                       > RESULT
 *  'A'..'H'    : (       0..7 )                             \
 *  'T'         : (       8    )   (DFA_INPUT_SYMBOL_T)       > (depends on defined following state or choice)
 *  '<'         : (       9    )   (possible extension)      /
 *  1..16       : (0x80 | 0..15) = 128..143                  \  set state 0..15
 *   ..32       : (0x80 |  ..31) =    ..159                   >            ..31
 *   ..64       : (0x80 |  ..63) =    ..191                  /             ..63
 *  'a'..'p'    : (0xC0 | 0..15) = 192..207                  -> (when defined and evaluated with result) set state 0..15
 */
void DfaChannel::transfer(const uint8_t input)
{
    // ensure the current state is valid, otherwhise following state is not defined (at least for regular symbols)
    if (!isValidState(_state))
    {
        logDebugP("State<int:%u>: transfer(int:%u)->IGNORE (current state not valid)", input, _state);
        addHistory(input, _state);
        return;
    }

    // 1) get the next state
    uint8_t nextState = transferGetNextForInput(input);

    logIndentUp();

    // 2) evaluate conditional states
    for (uint8_t i = 0; (64 <= nextState && nextState < 64 + DFA_DEF_CHOICESTATES_COUNT); i++)
    {
        if (i >= DFA_DEF_CHOICESTATES_COUNT)
        {
            // this should NEVER happen,
            // as transferEvaluateChoice is only allowed to produce monotonic increasing choicestates
            // but failing this condition would result in infinite loop
            logErrorP("ChoiceState<?>: Too many iterations!");
            nextState = DFA_STATE_UNDEFINED;
            break;
        }

        nextState = transferEvaluateChoice(nextState);
        // 2i) repeat until non-choice-state is reached
    }

    // 3) set the next state
    transferProcessNext(nextState);

    addHistory(input, _state); // write history with resulting state after processing
    logIndentDown();
}

uint8_t DfaChannel::transferGetNextForInput(const uint8_t input)
{
    uint8_t nextState = DFA_STATE_UNDEFINED; // must be uint8_t to ensure conversion from ETS-param to required state
    if (input < DFA_DEF_INPUTS_WITH_T_COUNT)
    {
        // 1a) regular symbols (X_z)
        // 1b) timeout symbols (X_t) // TODO check inclusion of '<'

        const uint16_t nextStateParamIdx = DFA_ParamCalcIndex(_transPRI[_state][input]);

        // Expected Values: ETS-Param => Converted by -1
        // 0 - no following state    => 255
        // 1-16/1-32/1-64 next state => 0-15/1-31/1-63
        // 65-80 choce states a..p   => 64-79
        // 127 timeout reset         => 126

        // must be uint8_t! 0x00 -> 0xff
        nextState = knx.paramByte(nextStateParamIdx) - 1;

        logDebugP("State<z%u>: transfer(%c)->%u", _state + 1, input == DFA_INPUT_SYMBOL_T ? 'T' : ('A' + input), nextState);
    }
    else if (input & 0x80)
    {
        // 1c) special case: direct setting state (X_z) and direct setting choice-states
        const uint8_t directState = (input & 0x7F);
        if (directState < DFA_DEF_STATES_COUNT)
        {
            // direct state
            nextState = directState;
            logDebugP("State<z%u>: transfer(%u)->%u", _state + 1, directState, directState);
        }
        else if (64 <= directState && directState < 64 + DFA_DEF_CHOICESTATES_COUNT)
        {
            // direct choice-state
            nextState = directState;
            logDebugP("State<z%u>: transfer(%c)->CHOICE", _state + 1, 'a' + directState - 64);
        }
        else
        {
            // NOT direct state and NOT choice state
        }
    }
    return nextState;
}

uint8_t DfaChannel::transferEvaluateChoice(const uint8_t nextState)
{
    // 2a) => is choice-state
    const uint8_t choiceState = nextState - 64;
    // TODO ensure allowed!
    if (choiceState >= DFA_DEF_CHOICESTATES_COUNT)
    {
        logErrorP("ChoiceState<?>: Wrong int:%u!", nextState);
        return DFA_STATE_UNDEFINED;
    }

    // 2b) get choice-state config
    // TODO ensure expected memory layout!
    const uint8_t choiceStateLogChannel = knx.paramByte(DFA_ParamCalcIndex(DFA_aCaLOG + choiceState * (DFA_aCbLOG - DFA_aCaLOG)));

    // 2c) check choice enabled
    if (choiceStateLogChannel == 0)
    {
        logInfoP("ChoiceState<%c>: Inactive!", 'a' + choiceState);
        return DFA_STATE_UNDEFINED;
    }

    // 2d) get assigned logic-channel
    const uint16_t logOutputKoNumber = getLogicOutputKoNumber(choiceStateLogChannel - 1);
    GroupObject *logOutputKo = &knx.getGroupObject(logOutputKoNumber);
    if (logOutputKo == nullptr)
    {
        logErrorP("ChoiceState<%c>: Undefined LOG[%u](KO %u)", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber);
        return DFA_STATE_UNDEFINED;
    }
    // const bool isLogicChannelEnabled = ... (Parameter calculated?)

    // 2e) check logic-channel result present
    if (logOutputKo->valueSize() != 1)
    {
        // TODO exclude all KOs of length 2 to 8 bits!
        logInfoP("ChoiceState<%c>: Invalid LOG[%u](KO %u) size %u", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber, logOutputKo->valueSize());
        return DFA_STATE_UNDEFINED;
    }
    uint8_t selectedNext;
    if (!logOutputKo->initialized())
    {
        logInfoP("ChoiceState<%c>: Uninitialized LOG[%u](KO %u)", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber);
        // 2g) get the following state
        // TODO ensure expected memory layout!
        selectedNext = knx.paramByte(DFA_ParamCalcIndex(DFA_aCaU + choiceState * (DFA_aCbU - DFA_aCaU)));
    }
    else
    {
        // 2f) get logic-channel result
        const bool choice = logOutputKo->value(DPT_Switch);
        logDebugP("ChoiceState<%c>: LOG[%u](KO %u)=%d", 'a' + choiceState, choiceStateLogChannel, logOutputKoNumber, choice);
        // 2g) get the following state
        // TODO ensure expected memory layout!
        selectedNext = choice
                           ? knx.paramByte(DFA_ParamCalcIndex(DFA_aCaT + choiceState * (DFA_aCbT - DFA_aCaT)))
                           : knx.paramByte(DFA_ParamCalcIndex(DFA_aCaF + choiceState * (DFA_aCbF - DFA_aCaF)));
    }

    const uint8_t selectedNextState = selectedNext - 1;
    if (isValidState(selectedNextState))
    {
        logDebugP("ChoiceState<%c>: -> selected next state z%u", 'a' + choiceState, selectedNextState + 1);
        return selectedNextState;
    }
    else if (selectedNextState == DFA_STATE_CHOICE_ELSE)
    {
        if (nextState + 1 < 64 + DFA_DEF_CHOICESTATES_COUNT)
        {
            logDebugP("ChoiceState<%c>: -> ELSE", 'a' + choiceState);
            return nextState + 1;
            // => start evaluating the chain until last choice-state
        }
        else
        {
            logErrorP("ChoiceState<%c>: Invalid ELSE for last Choice-State", 'a' + choiceState);
            return DFA_STATE_UNDEFINED;
        }
    }
    else
    {
        // 2h) ignore empty following
        // exclude arbitrary following choice-states (could result in endless loop!) or reset-pseudo-state
        logDebugP("ChoiceState<%c>: selected NO next state", 'a' + choiceState);
        // all next definitions not a state, or not explicitly else
        return DFA_STATE_UNDEFINED;
    }
}

void DfaChannel::transferProcessNext(const uint8_t nextState)
{
    if (isValidState(nextState))
    {
        // 3a) set state
        logDebugP("=> set state z%u", nextState + 1);
        setState(nextState);
    }
    else if (nextState == DFA_STATE_TIMEOUT_RESET)
    {
        // 3b) special case: timeout reset (without setting the state)
        logDebugP("=> timeout restart");

        // handling of timeout reset as defined by "<<", do not trigger any other reaction
        resetTimeout();
    }
    else if (nextState == DFA_STATE_UNDEFINED)
    {
        logDebugP("=> no following state");
    }
    else
    {
        logErrorP("=> UNEXPECTED int:%u", nextState);
    }
}

#pragma endregion "DFA_CHANNEL_TRANSFER"

#pragma region "DFA_CHANNEL_STATE_TIMEOUT"

void DfaChannel::endTimeout()
{
    if (_stateTimeoutDelay_ms > 0)
    {
        logDebugP("change timeout %d -> 1ms", _stateTimeoutDelay_ms);

        // set to shortest possible valid timeout of 1ms; might result in up to 1ms delay until end, when executed directly after state change
        _stateTimeoutDelay_ms = 1;
    }
}

void DfaChannel::resetTimeout()
{
    // do NOT check: if (_stateTimeoutDelay_ms > 0)
    _stateTimeoutBegin_ms = millis();
}

// TODO check definition of behaviour for non-timeout
uint32_t DfaChannel::timeoutRemaining_ms()
{
    // futureDelay = _stateTimeoutBegin_ms + _stateTimeoutDelay_ms - millis();
    // futureDelay = (_stateTimeoutBegin_ms - millis()) + _stateTimeoutDelay_ms;
    // futureDelay = _stateTimeoutDelay_ms - (millis() - _stateTimeoutBegin_ms)
    // TODO check for correct handling of overflow
    return _stateTimeoutDelay_ms - (millis() - _stateTimeoutBegin_ms);
}

#pragma endregion "DFA_CHANNEL_STATE_TIMEOUT"

#pragma region "DFA_CHANNEL_PERSISTANCE"

void DfaChannel::save()
{
    // 0x AR00_00PP
    const uint8_t conf = _channelActive << 7 | _running << 6 | ParamDFA_aStateRestore;
    openknx.flash.writeByte(conf);
    openknx.flash.writeByte(_state);

    const uint32_t futureDelay = timeoutRemaining_ms();
    openknx.flash.writeInt(futureDelay);

    // TODO write absolute time

    logDebugP("saved c=%2x s=%2x t=%u b=%u f=%u", conf, _state, _stateTimeoutDelay_ms, _stateTimeoutBegin_ms, futureDelay);
}

void DfaChannel::restore()
{
    // 0x AR00_00PP
    const uint8_t conf = openknx.flash.readByte();
    const uint8_t state = openknx.flash.readByte();
    const uint32_t timeout = openknx.flash.readInt();
    logDebugP("restored conf=0x%02x state=%3u(raw) timeout=%u", conf, state, timeout);

    // do not restore inactive channels, but must always read all bytes!
    if (conf & (1 << 7) == 0)
        return;

    //  <ParameterType Id="%AID%_PT-StatePersistance" Name="StatePersistance">
    //  <TypeRestriction Base="Value" SizeInBit="2">
    //      <Enumeration Id="%ENID%" Value="0" Text="nicht speichern (immer Startzustand nutzen)"  /><!-- 0b00 -->
    //      <Enumeration Id="%ENID%" Value="1" Text="gespeicherten Zustand neu starten"            /><!-- 0b01 -->
    //      <Enumeration Id="%ENID%" Value="2" Text="gespeicherten Zustand fortsetzen"             /><!-- 0b10 -->
    //      <!--
    //      <Enumeration Id="%ENID%" Value="3" Text="letzten Zustand mit absolutem Timeout-Ende"   /> --><!-- 0b11 -->
    //  </TypeRestriction>
    //  </ParameterType>

    if (ParamDFA_aStateRestore && (conf & 0b11))
    {
        // restore last running state
        if (ParamDFA_aStartPause > 0)
        {
            bool savedRunning = conf & (1 << 6);
            _firstRunning = savedRunning;
        }

        // restore only, if a state was reached; otherwise use z0
        if (isValidState(state))
        {
            _firstState = state;
            _firstStateTimeoutDelay_ms = timeout;

            _restoreOutputs = true;
        }
    }
}

#pragma endregion "DFA_CHANNEL_PERSISTANCE"

#pragma region "DFA_CHANNEL_COMMANDS"

bool DfaChannel::processCommandDfa(bool diagnoseKo)
{
    logDebugP("status and remaining delay");

    if (!_channelActive)
    {
        logInfoP("NOT_ACTIVE");
        if (diagnoseKo)
            openknx.console.writeDiagenoseKo("NOT_ACTIVE");
        return true;
    }

    const uint8_t state = _state + 1;
    const char mode = _running ? '<' : ']';
    if (state > 99)
    {
        // exclude states with > 2 characters; should never happen
    }
    else if (_stateTimeoutDelay_ms > 0)
    {
        uint32_t remaining = timeoutRemaining_ms();
        logDebugP("T@%d", remaining);
        const uint16_t timeoutMillis = remaining % 1000;
        remaining = remaining / 1000;
        const uint16_t timeoutSeconds = remaining % 60;
        remaining = remaining / 60;
        const uint16_t timeoutMinutes = remaining % 60;
        remaining = remaining / 60;
        const uint16_t timeoutHours = remaining;

        logInfoP((timeoutHours < 10) ? "%02d%c%d:%02d:%02d.%03d" : "%02d%c%5d:%02d:%02d", state, mode, timeoutHours, timeoutMinutes, timeoutSeconds, timeoutMillis);
        if (diagnoseKo)
            openknx.console.writeDiagenoseKo((timeoutHours < 10) ? "%02d%c%d:%02d:%02d.%03d" : "%02d%c%5d:%02d:%02d", state, mode, timeoutHours, timeoutMinutes, timeoutSeconds, timeoutMillis);
    }
    else
    {
        logInfoP("%02d%cNO_TIMEOUT", state, mode);
        if (diagnoseKo)
            openknx.console.writeDiagenoseKo("%02d%c NO_TIMEOUT", state, mode);
    }
    return true;
}

bool DfaChannel::processCommandDfaTimeout(bool diagnoseKo)
{
    logInfoP("timeout end now!");
    // TODO define behaviour when disabled
    endTimeout();
    return true;
}

bool DfaChannel::processCommandDfaStateSet(const uint8_t stateStarting1, bool diagnoseKo)
{
    const uint8_t state = stateStarting1 - 1;
    // TODO check setState returning valid state
    setState(state); // TODO check using transfer(..)
    return isValidState(state);
}

bool DfaChannel::processCommandDfaSymbolInsert(const uint8_t inputSymbolNumber, bool diagnoseKo)
{
    transfer(inputSymbolNumber);
    return true;
}

bool DfaChannel::processCommandDfaChoice(const uint8_t inputChoiceNumber, bool diagnoseKo)
{
    transfer(0xC0 | inputChoiceNumber);
    return true;
}

bool DfaChannel::processCommandDfaHistory(bool diagnoseKo)
{
    std::string historyStr = _history.getCompactHistoryString();
    logInfoP("History: %s", historyStr.c_str());
    if (diagnoseKo)
        openknx.console.writeDiagenoseKo(historyStr.c_str());
    return true;
}

#ifdef OPENKNX_DEBUG
bool DfaChannel::processCommandDfaTesting()
{
    uint8_t next[256];
    uint8_t eval[256];
    bool isState[256];
    bool isConditional[256];
    char type[256];
    logDebugP("TEST Collect:");
    logIndentUp();
    for (uint16_t i = 0x00; i <= 0xff; i++)
    {
        next[i] = transferGetNextForInput(i);
        eval[i] = transferEvaluateChoice(i);
        isState[i] = isValidState(i);
        isConditional[i] = (64 <= i && i < 64 + DFA_DEF_CHOICESTATES_COUNT);
        if (i < 8)
            type[i] = 'A' + i;
        else if (i == 8)
            type[i] = 'T';
        else if (128 <= i && i < 128 + DFA_DEF_STATES_COUNT)
            type[i] = '=';
        else if (128 + 64 <= i && i < 128 + 64 + DFA_DEF_CHOICESTATES_COUNT)
            type[i] = 'a' + (i - 128 - 64);
        else
            type[i] = '_';
    }
    logIndentDown();
    logDebugP("TEST[nnn]: T transf   S C choice");
    for (uint16_t i = 0x00; i <= 0xff; i++)
    {
        const uint16_t iFirst = i;
        logDebugP("TEST[%3u]: %c %3u|x%02x  %u %3u|x%02x", i, type[i], next[i], next[i], isState[i], isConditional[i], eval[i], eval[i]);
        while (i+1  <= 0xff && next[i+1] == next[i] && eval[i+1] == eval[i] && isState[i+1] == isState[i] && isConditional[i+1] == isConditional[i] && type[i+1] == type[i])
            i++;
        if (i > iFirst)
            logDebugP("... %ux ...", i - iFirst);
    }
    return true;
}
#endif

#pragma endregion "DFA_CHANNEL_COMMANDS"

void DfaChannel::addHistory(uint8_t input, uint8_t state)
{
    _history.addHistory(input, state);
    logDebugP("addHistory(input=int:%u, state=int:%u) [DONE]", input, state);
    logHexDebugP(_history.getHistoryBuffer(), _history.getHistoryBufferSize());
}
