Summary:	Small set of programs, which may be useful for pianists.
Name:		pianoutils
Version:	0.1.5
Release:	0
License:	GPL
Group:		Productivity/Multimedia/Sound
Source0:	%{name}-%{version}.tar.bz2

BuildRoot:	%{_tmppath}/%{name}-%{version}.%{release}-buildroot

Requires:	alsa
Requires:	libjack0
Requires:	libqt4 >= 4.2

BuildRequires:	libqt4-devel >= 4.2
BuildRequires:	alsa-devel

%description
PianoUtils is a small set of Qt-based programs, which may be useful for 
pianists. It's including metronome and keyboard splitter.

%prep
%setup

%build
%configure --prefix=%{buildroot}/usr
%__make

%install
%__make install

%clean
[ -d %{buildroot} -a "%{buildroot}" != "" ] && %__rm -rf %{buildroot}

%files
%{_bindir}/vmm
%{_bindir}/splitter
%{_datadir}/applications/VMM.desktop
%{_datadir}/applications/splitter.desktop
%{_datadir}/icons/hicolor/32x32/apps/pianoutils.png
%{_datadir}/locale/*_ru_RU.qm


