/**
  ******************************************************************************
  * @file    sine_model_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jan 17 16:24:24 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "sine_model_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_sine_model_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_sine_model_weights_array_u64[161] = {
  0xbe588232bf3f7679U, 0xbf3c9ee8bf1f1edaU, 0x3e9af9083fae3f83U, 0x3efe5d853e91a087U,
  0xbd169c7dbd89700bU, 0x3e92791abf252bd3U, 0x3e8965193ef83731U, 0xbeed12febdd9a5e0U,
  0x3f0a8b413a255065U, 0xbed653aeba8000d6U, 0xbe05265a3ecdc4d1U, 0x3f0c8178be79961cU,
  0xbe8d12f53ed04b90U, 0x3e4a3b0dbe996ac9U, 0x3ed6e71c3f0ae6edU, 0x3f02daa5be3409c2U,
  0xbe90b2023c9ef6d7U, 0xbbabeafcU, 0x3db10630U, 0xbf3b22d500000000U,
  0x3da6d341U, 0x3f13086900000000U, 0x3ea67f77bd7b923dU, 0xbe1542f400000000U,
  0x3e8fa5fd3ec4baeeU, 0x3e80fb5bbde247e4U, 0x3ec2961bbecf3b65U, 0xbeab108abe67c421U,
  0xbb0d6480bdee8659U, 0x3ebea89d3d093a50U, 0x3e762c37becee10aU, 0xbf1991fc3e8fe5cdU,
  0x3dadf8953f0b3e2cU, 0xbe3243cebec2b414U, 0xbe15bdc03e3e6786U, 0xbdbd5106bec22f13U,
  0xbd432fd03ea35e08U, 0xbe7616703ecc46c5U, 0xbe742c68be06b839U, 0xbe5f41d9bd988aecU,
  0xbe5b67ebbd22df9dU, 0x3eaeca0b3eb065b8U, 0x3ed4ab673eb392a3U, 0xbd863b31becae042U,
  0x3ea7fdcf3eb77f27U, 0x3e5678c7be5ca8baU, 0xbeaddd793ef7ad75U, 0x3eb19d6d3e7de7baU,
  0xbda82620bed0c745U, 0x3df0455cbe022a76U, 0xbd5a8d08bec0ce2dU, 0x3dc1d7493e9ef071U,
  0x3e59bbea3c7466d0U, 0x3f38b6f9be8c0b34U, 0xbdb48eaebeaf8053U, 0xbf2608143e1c4682U,
  0xbed5eaba3e47290aU, 0xbd0adf383eca33f3U, 0x3e19a38a3e08ad54U, 0xbf3967553eccde6fU,
  0xbc4360603e1b8c92U, 0x3e90823b3e883b51U, 0x3e4c3f82bbdeb12bU, 0xbdeab394be339950U,
  0xbcea99903f16ac61U, 0xbe95c55e3e13d46aU, 0xbd54d4e8be8fdaebU, 0xbcdfc7603ec24ad5U,
  0x3e82ce47bec7b87dU, 0x3e08090abed200bbU, 0xbe7c928abecd8315U, 0xbe95de553eceb675U,
  0x3e24eec1bde767d0U, 0xbc4087403e1cd8bcU, 0x3e3a8aeabe871ea5U, 0x3d8f1ba43eafecf3U,
  0xbd9bcbf03ebd623cU, 0x3ea6bf7fbedbda2eU, 0xbe2b94a63ea5d682U, 0xbeaf4881bec36098U,
  0xbc3886ca3e8617f7U, 0x3d3b5ff83d8046a9U, 0xbec95ae6be0ffd84U, 0x3e9065f23de3bd54U,
  0xbe709fbd3eb0f400U, 0x3e319bb33dbbf99cU, 0xbd13b30c3eaec2b5U, 0x3dd8fdf8bdb18cc0U,
  0xbe3f739bbec6f175U, 0x3c6cae203e9c93bfU, 0x3ea85789bdd0ea6aU, 0x3e69b9ecbea8b3a5U,
  0xbe72b3dbbe7ae4cbU, 0xbca537383cb18fc0U, 0xbdf1cf883e825de8U, 0x3d5da5d83ecf43f1U,
  0x3da693613f00e816U, 0x3dc2d2f43e92af9fU, 0x3e190c823d11c373U, 0x3ead02dbbec30ecfU,
  0xbd3dd1f83df2725eU, 0xbeba4bae3d17e1f0U, 0x3d4a01993ebf8799U, 0x3d91dadbbd9d6790U,
  0xbe3537cebe9ae401U, 0xbeba7baabeb12c16U, 0xbeb7b675be68c38dU, 0x3da7534dbd1a1980U,
  0xbd1761a83eb0160bU, 0x3e1373943db04414U, 0xbd81a6453e100696U, 0x3ee4fd293e488e0aU,
  0xbed3ca23bec7945fU, 0x3d0d6200be5da2edU, 0xbebb98a7bcd0b68dU, 0xbd743ad0be9ae498U,
  0xbe832a67bedfa322U, 0x3de1281dbe5cb33aU, 0x3ca6f0743e5c1a2eU, 0xbed97e7ebedd277aU,
  0x3db24070bccdac15U, 0x3e2eefd2bde453c0U, 0xbeb3c75dbede83d4U, 0xbcfe213e3ea736e7U,
  0x3eb0b529be311018U, 0xbc8dae133db1ef44U, 0x3ec19db33e9c5652U, 0xbe2a3770be911394U,
  0xbebbca8bbedb2425U, 0x3de55d643e8af72dU, 0xbe901cdfbebb07cbU, 0x3df2315c3d87b9c0U,
  0x3ced2990be117fefU, 0x3ea2298f3ec83f27U, 0x3e453d0dbe55eb4eU, 0xbda9b220be98fabcU,
  0xbea3abe7be965f2fU, 0xbe6466923df3d4f4U, 0xbda708ecbc18994cU, 0x3dfd70fdbe9b306aU,
  0x3dd4ffc43e2dd352U, 0xbd94d9c7beb0ea73U, 0xbe3d8010bd077791U, 0xbcd47fb33e12cee6U,
  0xbeae36c73d9015fdU, 0x3de71e1c3ec6cadfU, 0x3e6b8dce3cd342b5U, 0x3ec399b23e86577dU,
  0x3e54deaebdd8d131U, 0xbe8042d93e7dcb56U, 0xbd7db36dbe7edc5fU, 0x3ea1ac40be9eea08U,
  0x3ee0931a3d5480e8U, 0xbe12fd4ebcadb338U, 0x3efed0cd3ee60829U, 0xbabc1bc400000000U,
  0x3e523ae3ba2a15f0U, 0xbe2678b1be4c4c19U, 0xbd3d9785bd444698U, 0xbc5d59b9bdcd5cb2U,
  0xbc2183b9U,
};


ai_handle g_sine_model_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_sine_model_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

