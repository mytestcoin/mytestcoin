// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (  0, uint256("0x00000fe7342ee193f07bef99631b5f4e023c3513c3fba11da43e6a8b3fa991d1"))
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1505039400, // * UNIX timestamp of last checkpoint block
    0,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1100        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    ( 0, uint256("0x000009c7fcb6abbfb079f21624695dd20961fb69b6033d6c60c47850c854d216"))
    ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1505039401,
    0,
    500
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    ( 0, uint256("0x6c08da56edfd5c19285831205a7ee3bf5eb5c049ca6f754b46e34c2827ff45f1"))
    ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0x0c;
        pchMessageStart[2] = 0x6b;
        pchMessageStart[3] = 0xbd;
        vAlertPubKey = ParseHex("044a91920af82ae1f31ae1ba261623a4ba6cea763eadc0735278ab7867996d8c421ba9bbc012447dda99380ee139743a4ca9bd7b4e00e3020efabe5ab47efcb07a");
        nDefaultPort = 17718;
        bnProofOfWorkLimit = ~uint256(0) >> 20;  // Sibcoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // Sibcoin: 1 day
        nTargetSpacing = 2.5 * 60; // Sibcoin: 2.5 minutes

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "start test sibcoin fork 10/09/2017 10/30";
        CMutableTransaction txNew;

        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0432e2ca0497210c03129ad67b8a0bcdc37040d53c5a16094ef9d84cbd95d2be0a757e7668402347b488f9c322620d7421440aac305dc3c08e2711b58d9e715cca") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1505039400;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 161166;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000fe7342ee193f07bef99631b5f4e023c3513c3fba11da43e6a8b3fa991d1"));
        assert(genesis.hashMerkleRoot == uint256("0xd7a67a64a640412cdaf199f350af5ac6c5fb22164ffb3d262f52b0a84178665a"));

        vSeeds.clear();

/*        vSeeds.push_back(CDNSSeedData("chervonec.info", "dnsseed.chervonec.info"));
        vSeeds.push_back(CDNSSeedData("darknode1", "dnsseed1.darknode.ru"));
        vSeeds.push_back(CDNSSeedData("darknode2", "dnsseed2.darknode.ru"));
        vSeeds.push_back(CDNSSeedData("darknode3", "dnsseed3.darknode.ru"));
*/
#if __cplusplus > 199711L
        base58Prefixes[PUBKEY_ADDRESS] = {63};                  // Sibcoin addresses start with 'S'
        base58Prefixes[SCRIPT_ADDRESS] = {40};					// Sibcoin script addresses start with 'H'
        base58Prefixes[SECRET_KEY] =     {128};                 // Sibcoin private keys start with '5'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04,0x88,0xB2,0x1E}; // Sibcoin BIP32 pubkeys start with 'xpub'
        base58Prefixes[EXT_SECRET_KEY] = {0x04,0x88,0xAD,0xE4}; // Sibcoin BIP32 prvkeys start with 'xprv'
        base58Prefixes[EXT_COIN_TYPE]  = {0x2D,0x00,0x00,0x80}; // Sibcoin BIP44 coin type is '45'
#else
        base58Prefixes[PUBKEY_ADDRESS] = list_of( 63);                    // Sibcoin addresses start with 'S'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 40);                    // Sibcoin script addresses start with 'H'
        base58Prefixes[SECRET_KEY] =     list_of(128);                    // Sibcoin private keys start with '5'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E); // Sibcoin BIP32 pubkeys start with 'xpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4); // Sibcoin BIP32 prvkeys start with 'xprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x8000002D);             // Sibcoin BIP44 coin type is '45'

#endif
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04c877948d5354afc8ab4e3cf1b8d12ad575d36616455f85db39e4ebd05afdff80ec733627821b9d2454b146cac45bdac1c04b17e96b122999c8a427918b61de79";
        strMasternodePaymentsPubKey = "04c877948d5354afc8ab4e3cf1b8d12ad575d36616455f85db39e4ebd05afdff80ec733627821b9d2454b146cac45bdac1c04b17e96b122999c8a427918b61de79";
        strDarksendPoolDummyAddress = "SXs9PLTEbFhCh4efZ7VkuEgiw7ca7V7FNx";
        nStartMasternodePayments = 1505039400; //Sun, 09 Aug 2015 00:00:00 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("045938097ac24552a3963ef26715e73b4c4e921bf0f2f0fbe747adc1f1498eebd255306ee2f4c8700d99ecbd1abedf3810a4dcb5bbfbabd37ce7b558a9045b935b");
        nDefaultPort = 17719;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // Dash: 1 day
        nTargetSpacing = 2.5 * 60; // Dash: 2.5 minutes

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1505039401;
        genesis.nNonce = 2972519;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000009c7fcb6abbfb079f21624695dd20961fb69b6033d6c60c47850c854d216"));

        vFixedSeeds.clear();
        vSeeds.clear();
        /*vSeeds.push_back(CDNSSeedData("dashpay.io", "testnet-seed.dashpay.io"));
        vSeeds.push_back(CDNSSeedData("dash.qa", "testnet-seed.dash.qa"));
        */
#if __cplusplus > 199711L
        base58Prefixes[PUBKEY_ADDRESS] = {125};                     // Testnet sibcoin addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = {100};						// Testnet sibcoin script addresses start with 'h'
        base58Prefixes[SECRET_KEY]     = {239};						// Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04,0x35,0x87,0xCF};		// Testnet sibcoin BIP32 pubkeys start with 'tpub'
        base58Prefixes[EXT_SECRET_KEY] = {0x04,0x35,0x83,0x94};		// Testnet sibcoin BIP32 prvkeys start with 'tprv'
        base58Prefixes[EXT_COIN_TYPE]  = {0x01,0x00,0x00,0x80};		// Testnet sibcoin BIP44 coin type is '1' (All coin's testnet default)
#else
        base58Prefixes[PUBKEY_ADDRESS] = list_of(125);                    // Testnet sibcoin addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(100);                    // Testnet sibcoin script addresses start with 'h'
        base58Prefixes[SECRET_KEY]     = list_of(239);                    // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF); // Testnet sibcoin BIP32 pubkeys start with 'tpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94); // Testnet sibcoin BIP32 prvkeys start with 'tprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet sibcoin BIP44 coin type is '1' (All coin's testnet default)
#endif
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04a50ce4863fc5d1613c1c067710824c46b9b0f59dfe5adb2be1ddf00ba2f445eb529b68d336612700c33d44ddb3f8d71aee6c73df1851dea608b4caa4a4ad135f";
        strMasternodePaymentsPubKey = "04a50ce4863fc5d1613c1c067710824c46b9b0f59dfe5adb2be1ddf00ba2f445eb529b68d336612700c33d44ddb3f8d71aee6c73df1851dea608b4caa4a4ad135f";
        strDarksendPoolDummyAddress = "sMrxXJMxATgLRxPtnYwMEn58xUg8WJnX7U";
        nStartMasternodePayments = 1505039401; //Thu, 09 Jul 2015 00:00:00 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Sibcoin: 1 day
        nTargetSpacing = 2.5 * 60; // Sibcoin: 2.5 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1505039402;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 17720;
        assert(hashGenesisBlock == uint256("0x6c08da56edfd5c19285831205a7ee3bf5eb5c049ca6f754b46e34c2827ff45f1"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18334;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
