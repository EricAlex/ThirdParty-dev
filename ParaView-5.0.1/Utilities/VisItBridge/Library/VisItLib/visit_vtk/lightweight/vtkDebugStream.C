/*****************************************************************************
*
* Copyright (c) 2000 - 2013, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#include <vtkDebugStream.h>

#include <vtkObjectFactory.h>

#include <DebugStream.h>


// *****************************************************
// Modifications:
//   Kathleen Bonnell, Wed Mar  6 13:48:48 PST 2002
//   Use macro for 'New' method.
// *****************************************************

vtkStandardNewMacro(vtkDebugStream);

// *****************************************************
// Modifications:
//   Cyrus Harrison, Sat Aug 11 20:37:23 PDT 2007
//   Added init of filterFrequentEvents
// *****************************************************
bool vtkDebugStream::filterFrequentEvents = false;

// *****************************************************
// Modifications:
//   Hank Childs, Tue Mar 22 16:19:59 PST 2005
//   Fix memory leak.
// *****************************************************

void vtkDebugStream::Initialize(void)
{
  vtkDebugStream *ds = vtkDebugStream::New();
  vtkOutputWindow::SetInstance(ds);
  ds->Delete();
}

// *****************************************************
// Modifications:
//   Cyrus Harrison, Sat Aug 11 20:37:23 PDT 2007
//   Added a filter for frequent events to reduce
//   strain on file system.
// *****************************************************
void vtkDebugStream::DisplayText(const char *txt)
{
    // exclude very frequent events to spare the fs
  if(filterFrequentEvents)
  {
      bool ok = true;
      ok = ok && strstr(txt,"Returning cell type") == NULL;
      
      if(ok)
      {debug1 << txt << endl;}
  }
  else
  {debug1 << txt << endl;}

}
