/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef mitkNDIAuroraTypeInformation_h
#define mitkNDIAuroraTypeInformation_h

#include <MitkIGTExports.h>

#include "mitkTrackingDeviceTypeInformation.h"

namespace mitk
{
  class MITKIGT_EXPORT NDIPAuroraTypeInformation : public TrackingDeviceTypeInformation
  {
    public:
      NDIPAuroraTypeInformation();
      virtual ~NDIPAuroraTypeInformation();

      virtual TrackingDeviceSource::Pointer CreateTrackingDeviceSource(mitk::TrackingDevice::Pointer trackingDevice,
                                                                       mitk::NavigationToolStorage::Pointer navigationTools,
                                                                       std::string* errorMessage,
                                                                       std::vector<int>* toolCorrespondencesInToolStorage) override;
  };
} // namespace mitk

#endif //mitkNDIAuroraTypeInformation_h
