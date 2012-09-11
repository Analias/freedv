//==========================================================================
// Name:            fdmdv2_main.h
//
// Purpose:         Declares simple wxWidgets application with GUI.
// Created:         Apr. 9, 2012
// Initial author:  David Witten
// License:         BSD License (other licenses may apply to other
//                  components of this project)
//==========================================================================
#ifndef __FDMDV2_MAIN__
#define __FDMDV2_MAIN__

#include <wx/wx.h>

#include "wx/file.h"
#include "wx/filename.h"
#include "wx/graphics.h"
#include "wx/mstream.h"
#include "wx/wfstream.h"
#include "wx/quantize.h"
#include "wx/scopedptr.h"
#include "wx/stopwatch.h"
#include "wx/versioninfo.h"
#include <wx/sound.h>
//#include <wx/thread.h>

#include "codec2.h"
#include "fdmdv.h"

#include "topFrame.h"
#include "dlg_about.h"
#include "dlg_audio.h"
#include "dlg_options.h"
#include "dlg_comports.h"
#include "fdmdv2_plot.h"
#include "fdmdv2_plot_scalar.h"
#include "fdmdv2_plot_scatter.h"
#include "fdmdv2_plot_waterfall.h"
#include "fdmdv2_plot_spectrum.h"
#include "fdmdv2_pa_wrapper.h"
#include "sndfile.h"
#include "portaudio.h"

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=
// Class MainApp
//
// @class $(Name)
// @author $(User)
// @date $(Date)
// @file $(CurrentFileName).$(CurrentFileExt)
// @brief
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=
class MainApp : public wxApp
{
    public:
        virtual bool OnInit();
        virtual int OnExit()
        {
            return 0;
        }

    protected:
};

// declare global static function wxGetApp()
DECLARE_APP(MainApp)

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=
// Class MainFrame
//
// @class $(Name)
// @author $(User)
// @date $(Date)
// @file $(CurrentFileName).$(CurrentFileExt)
// @brief
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=
class MainFrame : public TopFrame
{
    public:
        MainFrame(wxWindow *parent);
        virtual ~MainFrame();

        PlotPanel*      m_panelDefaultA;
        PlotSpectrum*   m_panelSpectrum;
        PlotWaterfall*  m_panelWaterfall;
        PlotScatter*    m_panelScatter;
        PlotScalar*     m_panelScalar;
        bool            m_SquelchActive;
        bool            m_RxRunning;
        bool            m_TxRunning;
        CODEC2          *m_RXCodec2;
        CODEC2          *m_TXCodec2;
        PortAudioWrap   *m_rxPa;
        PortAudioWrap   *m_txPa;
        PaDeviceIndex   m_rxDevIn;
        PaDeviceIndex   m_rxDevOut;
        PaDeviceIndex   m_txDevIn;
        PaDeviceIndex   m_txDevOut;
        PaError         m_rxErr;
        PaError         m_txErr;
        wxSound         *m_sound;

        static int rxCallback(
                                const void *inBuffer,
                                void *outBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *outTime,
                                PaStreamCallbackFlags statusFlags,
                                void *userData
                             );
        static int txCallback(
                                const void *inBuffer,
                                void *outBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *outTime,
                                PaStreamCallbackFlags statusFlags,
                                void *userData
                             );

    protected:
        // protected event handlers
        virtual void OnCloseFrame(wxCloseEvent& event);
        virtual void OnExitClick(wxCommandEvent& event);

        void startTxStream();
        void startRxStream();
        void stopTxStream();
        void stopRxStream();
        void abortTxStream();
        void abortRxStream();
        void OnOpen( wxCommandEvent& event );
        void OnOpenUpdateUI( wxUpdateUIEvent& event );
        void OnSave( wxCommandEvent& event );
        void OnSaveUpdateUI( wxUpdateUIEvent& event );
        void OnClose( wxCommandEvent& event );
        void OnCloseUpdateUI( wxUpdateUIEvent& event );
        void OnExit( wxCommandEvent& event );
        void OnCopy( wxCommandEvent& event );
        void OnCopyUpdateUI( wxUpdateUIEvent& event );
        void OnCut( wxCommandEvent& event );
        void OnCutUpdateUI( wxUpdateUIEvent& event );
        void OnPaste( wxCommandEvent& event );
        void OnPasteUpdateUI( wxUpdateUIEvent& event );
        void OnToolsAudio( wxCommandEvent& event );
        void OnToolsAudioUI( wxUpdateUIEvent& event );
        void OnToolsComCfg( wxCommandEvent& event );
        void OnToolsComCfgUI( wxUpdateUIEvent& event );
        void OnToolsOptions( wxCommandEvent& event );
        void OnToolsOptionsUI( wxUpdateUIEvent& event );
        void OnCaptureRxStream( wxCommandEvent& event );
        void OnCaptureTxStream( wxCommandEvent& event );
        void OnPlayAudioFile( wxCommandEvent& event );
        void OnHelpCheckUpdates( wxCommandEvent& event );
        void OnHelpCheckUpdatesUI( wxUpdateUIEvent& event );
        void OnHelpAbout( wxCommandEvent& event );
        void OnCmdSliderScroll( wxScrollEvent& event );
        void OnSliderScrollBottom( wxScrollEvent& event );
        void OnCmdSliderScrollChanged( wxScrollEvent& event );
        void OnSliderScrollTop( wxScrollEvent& event );
        void OnCheckSQClick( wxCommandEvent& event );
        // Toggle Buttons
        void OnTogBtnSplitClick(wxCommandEvent& event);
        void OnTogBtnAnalogClick(wxCommandEvent& event);
        void OnTogBtnALCClick(wxCommandEvent& event);
        void OnTogBtnRxID( wxCommandEvent& event );
        void OnTogBtnTxID( wxCommandEvent& event );
        void OnTogBtnTXClick( wxCommandEvent& event );
        void OnTogBtnOnOff( wxCommandEvent& event );
        void OnPaint(wxPaintEvent& event);
        void OnClose( wxCloseEvent& event );
        void OnSize( wxSizeEvent& event );
        void OnUpdateUI( wxUpdateUIEvent& event );

        wxString LoadUserImage(wxImage& image);

    private:
        bool CreateSound(wxSound& snd) const;

        wxString    m_soundFile;
#ifdef __WXMSW__
        wxString    m_soundRes;
#endif // __WXMSW__
        bool        m_useMemory;

        wxTextCtrl* m_tc;
        int         m_zoom;
};

#endif //__FDMDV2_MAIN__