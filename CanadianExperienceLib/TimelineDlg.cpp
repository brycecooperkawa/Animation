/**
 * @file TimelineDlg.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "Timeline.h"
#include "TimelineDlg.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>

/**
 * Constructor
 * @param parent The parent window we will center in
 * @param timeline Pointer to the timeline we are editing
 */
TimelineDlg::TimelineDlg(wxWindow* parent, Timeline* timeline) : mTimeline(timeline)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"TimelineDlg");

    mNumberOfFrames = timeline->GetNumFrames();
    mFrameRate = timeline->GetFrameRate();

    auto numFramesCtrl = XRCCTRL(*this, "TimelineDlgNumFrames", wxTextCtrl);
    wxIntegerValidator<int> numFramesValidator(&mNumberOfFrames);
    numFramesValidator.SetRange(1, 10000);
    numFramesCtrl->SetValidator(numFramesValidator);

    auto numFrameRateCtrl = XRCCTRL(*this, "TimelineDlgFrameRate", wxTextCtrl);
    wxIntegerValidator<int> numFrameRateValidator(&mFrameRate);
    numFrameRateValidator.SetRange(1, 60);
    numFrameRateCtrl->SetValidator(numFrameRateValidator);

    Bind(wxEVT_BUTTON, &TimelineDlg::OnOK, this, wxID_OK);

}

/**
 * Handle an OK button press
 * @param event Button event
 */
void TimelineDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mTimeline->SetNumFrames(mNumberOfFrames);
        mTimeline->SetFrameRate(mFrameRate);

        EndModal(wxID_OK);
    }
}