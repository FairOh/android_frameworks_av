LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	src/add.cpp \
 	src/az_lsp.cpp \
 	src/bitno_tab.cpp \
 	src/bitreorder_tab.cpp \
 	src/bits2prm.cpp \
 	src/bytesused.cpp \
 	src/c2_9pf_tab.cpp \
 	src/copy.cpp \
 	src/div_32.cpp \
 	src/div_s.cpp \
 	src/extract_h.cpp \
 	src/extract_l.cpp \
 	src/gains_tbl.cpp \
 	src/gc_pred.cpp \
 	src/gmed_n.cpp \
 	src/grid_tbl.cpp \
 	src/gray_tbl.cpp \
 	src/int_lpc.cpp \
 	src/inv_sqrt.cpp \
 	src/inv_sqrt_tbl.cpp \
 	src/l_abs.cpp \
 	src/l_deposit_h.cpp \
 	src/l_deposit_l.cpp \
 	src/l_shr_r.cpp \
 	src/log2.cpp \
 	src/log2_norm.cpp \
 	src/log2_tbl.cpp \
 	src/lsfwt.cpp \
 	src/lsp.cpp \
 	src/lsp_az.cpp \
 	src/lsp_lsf.cpp \
 	src/lsp_lsf_tbl.cpp \
 	src/lsp_tab.cpp \
 	src/mult_r.cpp \
 	src/norm_s.cpp \
 	src/overflow_tbl.cpp \
 	src/ph_disp_tab.cpp \
 	src/pow2.cpp \
 	src/pow2_tbl.cpp \
 	src/q_plsf.cpp \
 	src/q_plsf_3.cpp \
 	src/q_plsf_3_tbl.cpp \
 	src/q_plsf_5.cpp \
 	src/q_plsf_5_tbl.cpp \
 	src/qua_gain_tbl.cpp \
 	src/reorder.cpp \
 	src/round.cpp \
 	src/set_zero.cpp \
 	src/shr.cpp \
 	src/shr_r.cpp \
 	src/sqrt_l.cpp \
 	src/sqrt_l_tbl.cpp \
 	src/sub.cpp \
 	src/vad1.cpp \
 	src/weight_a.cpp \
 	src/window_tab.cpp

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/include

LOCAL_CFLAGS := \
        -DOSCL_UNUSED_ARG= -DOSCL_IMPORT_REF= -DOSCL_EXPORT_REF=

ifeq ($(TARGET_ARCH),mips)
    ifneq ($(ARCH_HAS_BIGENDIAN),true)
       ifeq ($(ARCH_MIPS_DSP_REV),2)
            LOCAL_CFLAGS += -DMIPS_DSP_R2_LE
            LOCAL_SRC_FILES  += src/mips/norm_l_mips.cpp \
                                src/mips/pred_lt_mips.cpp \
                                src/mips/q_plsf_3_mips.cpp \
                                src/mips/residu_mips.cpp \
                                src/mips/syn_filt_mips.cpp
        else
            ifeq ($(ARCH_MIPS_DSP_REV),1)
                LOCAL_CFLAGS += -DMIPS_DSP_R1_LE
                LOCAL_SRC_FILES += src/mips/norm_l_mips.cpp \
                                src/mips/pred_lt_mips.cpp \
                                src/mips/q_plsf_3_mips.cpp \
                                src/mips/residu_mips.cpp \
                                src/mips/syn_filt_mips.cpp
            else
                LOCAL_CFLAGS += -DMIPS32_R2_LE
                LOCAL_SRC_FILES += src/mips/norm_l_mips.cpp \
                                src/mips/pred_lt_mips.cpp \
                                src/mips/q_plsf_3_mips.cpp \
                                src/mips/residu_mips.cpp \
                                src/mips/syn_filt_mips.cpp
            endif
        endif
    else
        LOCAL_SRC_FILES += src/norm_l.cpp \
                           src/pred_lt.cpp \
                           src/residu.cpp \
                           src/syn_filt.cpp
    endif
else
    LOCAL_SRC_FILES += src/norm_l.cpp \
                       src/pred_lt.cpp \
                       src/residu.cpp \
                       src/syn_filt.cpp
endif

LOCAL_MODULE := libstagefright_amrnb_common

include $(BUILD_SHARED_LIBRARY)
