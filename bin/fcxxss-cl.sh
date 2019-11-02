#!/bin/bash
#
# Fornux C++ Superset Source-to-Source Compiler 5.0
#
# Copyright (c) Fornux Inc. 2019
#

usage() 
{
    echo "Usage: $0 [options] file"
    echo
    echo "Fornux C++ Superset Source-to-Source Compiler 5.0 (for clang-cl)"
}

CCFLAGS="-Wno-shadow -Wno-unused-parameter -Wno-unused-value -Wno-missing-prototypes -Wno-format-security -Wno-extern-initializer -Wno-gcc-compat -Wno-null-dereference -Wno-exit-time-destructors -Wno-unused-command-line-argument -fexceptions -DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_DISABLE_THREADS"
LDFLAGS="-lstdc++"

GETOPT=$(getopt -a -o vcSEwCsI:L:D:U:o:f:W::m:g::O::x:d:l:B:b:V: -l username:,compiler:,linker:,pipe,ansi,std:,traditional,traditional-cpp,pedantic,pedantic-errors,nostartfiles,nodefaultlibs,nostdlib,pie,rdynamic,static,static-libgcc,static-libstdc++,shared,shared-libgcc,symbolic,threads,pthreads,pthread,version,param:,idirafter:,include:,isystem:,c-isystem:,cxx-isystem:,imacros:,iprefix:,iwithprefix:,iwithprefixbefore:,isystem:,imultilib:,isysroot:,iquote:,specs:,sysroot:,param:,soname:,Xpreprocessor:,Xassembler:,Xlinker:,M,MM,MF:,MG,MP,MT:,MQ:,MD,MMD -n $0 -- "$@")

if [[ $? != 0 ]] ; then usage ; exit 1 ; fi

eval set -- "$GETOPT"

while true ; do
    case "$1" in
        -v) OPT+="$1 " ; shift 1 ;;
        -c) COMPILE+="$1 " ; shift 1 ;;
        -S) OPT+="$1 " ; shift 1 ;;
        -E) OPT+="$1 -I $FCXXSS_DIR/include "; shift 1 ;;
        -w) OPT+="$1 " ; shift 1 ;;
        -C) OPT+="$1 " ; shift 1 ;;
        -s) OPT+="$1 " ; shift 1 ;;
        -I) INCLUDE+="-iquote $2 " ; shift 2 ;;
        -L) OPT+="$1$2 " ; shift 2 ;;
        -D) DEFINE+="$1$2 " ; shift 2 ;;
        -U) OPT+="$1$2 " ; shift 2 ;;
        -o) OUTPUT="$1$2" ; shift 2 ;;
        -f) OPT+="$1$2 " ; DEBUG+="$1$2" ; if [[ "$2" =~ ^openmp.* ]]; then OPENMP="$($FCXXSS_CC -fopenmp -dM -E - < /dev/null | grep -i _OPENMP | awk '{print $3;}')"; DEFINE+="-D_OPENMP=$OPENMP "; fi; shift 2 ;;
        -W) OPT+="$1$2 " ; shift 2 ;;
        -m) OPT+="$1$2 " ; shift 2 ;;
        -g) OPT+="$1$2 " ; DEBUG+="$1$2" ; shift 2 ;;
        -O) OPT+="$1$2 " ; DEBUG+="$1$2" ; shift 2 ;;
        -x) OPT+="$1$2 " ; shift 2 ;;
        -d) OPT+="$1$2 " ; shift 2 ;;
        -l) LIBRARY+="$1$2 " ; shift 2 ;;
        -B) OPT+="$1$2 " ; shift 2 ;;
        -b) OPT+="$1$2 " ; shift 2 ;;
        -V) OPT+="$1$2 " ; shift 2 ;;
        --pipe) OPT+="$1 " ; shift 1 ;;
        --ansi) OPT+="$1 " ; shift 1 ;;
        --traditional) OPT+="$1 " ; shift 1 ;;
        --traditional-cpp) OPT+="$1 " ; shift 1 ;;
        --pedantic) OPT+="$1 " ; shift 1 ;;
        --pedantic-errors) OPT+="$1 " ; shift 1 ;;
        --nostartfiles) OPT+="$1 " ; shift 1 ;;
        --nodefaultlibs) OPT+="$1 " ; shift 1 ;;
        --nostdlib) OPT+="$1 " ; shift 1 ;;
        --pie) OPT+="$1 " ; shift 1 ;;
        --rdynamic) OPT+="-rdynamic " ; shift 1 ;;
        --static) OPT+="$1 " ; shift 1 ;;
        --static-libgcc) OPT+="$1 " ; shift 1 ;;
        --static-libstdc++) OPT+="$1 " ; shift 1 ;;
        --shared) OPT+="$1 " ; shift 1 ;;
        --shared-libgcc) OPT+="$1 " ; shift 1 ;;
        --symbolic) OPT+="$1 " ; shift 1 ;;
        --threads) OPT+="$1 " ; shift 1 ;;
        --pthreads) OPT+="$1 " ; shift 1 ;;
        --pthread) OPT+="-pthread " ; shift 1 ;;
        --version) OPT+="$1 " ; shift 1 ;;
        --std) shift 2 ;;
        --param) OPT+="$1 $2 " ; shift 2 ;;
        --idirafter) OPT+="$1 $2 " ; shift 2 ;;
        --include) OPT+="$1 $2 " ; shift 2 ;;
        --isystem) ISYSTEM+="-isystem $2 " ; shift 2 ;;
        --c-isystem) ISYSTEM+="-c-isystem $2 " ; shift 2 ;;
        --cxx-isystem) ISYSTEM+="-cxx-isystem $2 " ; shift 2 ;;
        --imacros) OPT+="$1 $2 " ; shift 2 ;;
        --iprefix) OPT+="$1 $2 " ; shift 2 ;;
        --iwithprefix) OPT+="$1 $2 " ; shift 2 ;;
        --iwithprefixbefore) OPT+="$1 $2 " ; shift 2 ;; 
        --imultilib) OPT+="$1 $2 " ; shift 2 ;;
        --isysroot) OPT+="$1 $2 " ; shift 2 ;;
        --iquote) OPT+="$1 $2 " ; shift 2 ;;
        --specs) OPT+="$1 $2 " ; shift 2 ;;
        --sysroot) OPT+="$1 $2 " ; shift 2 ;;
        --param) OPT+="$1 $2 " ; shift 2 ;;
        --soname) OPT+="-install_name $2 " ; shift 2 ;;
        --Xpreprocessor) OPT+="$1 $2 " ; shift 2 ;;
        --Xassembler) OPT+="$1 $2 " ; shift 2 ;;
        --Xlinker) OPT+="$1 $2 " ; shift 2 ;;
        --M) PPOUTPUT+="-M " ; shift 1 ;;
        --MM) PPOUTPUT+="-MM " ; shift 1 ;;
        --MF) PPOUTPUT+="-MF $2 " ; shift 2 ;;
        --MG) PPOUTPUT+="-MG " ; shift 1 ;;
        --MP) PPOUTPUT+="-MP " ; shift 1 ;;
        --MT) PPOUTPUT+="-MT $2 " ; shift 2 ;;
        --MQ) PPOUTPUT+="-MQ $2 " ; shift 2 ;;
        --MD) PPOUTPUT+="-MD " ; shift 1 ;;
        --MMD) PPOUTPUT+="-MMD " ; shift 1 ;;
        --) shift ; break ;;
    esac
done

#set -x

RED='\033[1;31m'
YELLOW='\033[1;33m'
NOCOLOR='\033[0m'

if [[ ! -z "$@" ]]; then
    case "$@" in
    *.c)
        STD="-xc -std=c99"
        ;;
    *.cc|*.cxx|*.cpp|*.c++)
        STD="-xc++ -std=c++11"
        ;;
    *.o|*.obj)
        ;;
    *)
        (>&2 echo "$0: unrecognized file format")
        exit 1
        ;;
    esac

    if [[ ! -z "$STD" ]]; then
        if [[ -z "$FCXXSS_CC" ]]; then
            (>&2 echo "$0: compiler not set")
            exit 1
        fi

        TEMPLOCK="$(echo $(pwd) | md5sum | cut -d ' ' -f1)"
        TEMPFILE="$@"
        TEMPDIR="/var/tmp/fcxxss/$TEMPLOCK"
        TEMPSUBDIR=$(dirname "$TEMPFILE")
        
        mkdir -p "$TEMPDIR/$TEMPSUBDIR"
            
		if [[ ! -z "$COMPILE" ]] && [[ -z "$OUTPUT" ]]; then
			OUTPUT+="-o $(echo $@ | sed 's/\..*$/.o/')"
		fi

		printf "${YELLOW}>>> Pass 1${NOCOLOR}\n"
        if $FCXXSS_CC $STD $DEFINE "$INCLUDE" -E "$@" -w | $FCXXSS_DIR/bin/ffldwuc -aup > "$TEMPDIR/$TEMPFILE.pass1.cxx"; then
		
			printf "${YELLOW}>>> Pass 2${NOCOLOR}\n"
			if $FCXXSS_DIR/bin/fcxxss -ast-print "$TEMPDIR/$TEMPFILE".pass1.cxx -- "$ISYSTEM" --driver-mode=cl /EHa /w | $FCXXSS_DIR/bin/ffldwuc -amp > "$TEMPDIR/$TEMPFILE.pass2.cxx"; then
			
				printf "${YELLOW}>>> Pass 3${NOCOLOR}\n"
				if $FCXXSS_CC $DEFINE $INCLUDE $ISYSTEM $OPT $CCFLAGS -I "$FCXXSS_DIR/include" -I "$FCXXSS_DIR/root_ptr/include" -include "$FCXXSS_DIR/include/fcxxss.h" -include windows.h $($FCXXSS_DIR/bin/cygpath -awp "$TEMPDIR/$TEMPFILE.pass2.cxx") "$COMPILE" "$OUTPUT" "$PPOUTPUT" $LIBRARY $LDFLAGS -w; then
					exit 0
				else
					(>&2 printf "${RED}$0: intermediate files '$TEMPDIR/$TEMPFILE.pass?.cxx${NOCOLOR}\n")
					exit 1
				fi
			else
				(>&2 printf "${RED}$0: intermediate file '$TEMPDIR/$TEMPFILE.pass2.cxx${NOCOLOR}\n")
				exit 1
			fi
		else
			(>&2 printf "${RED}$0: intermediate file '$TEMPDIR/$TEMPFILE.pass1.cxx${NOCOLOR}\n")
			exit 1
		fi
    else
        if [[ -z "$FCXXSS_LD" ]]; then
            (>&2 printf "${RED}$0: linker not set${NOCOLOR}\n")
            exit 1
        fi

        $FCXXSS_LD $OPT "$@" $LIBRARY $LDFLAGS "$OUTPUT"
    fi
else
    if [[ -z "$FCXXSS_CC" ]]; then
        (>&2 printf "${RED}$0: compiler not set${NOCOLOR}\n")
        exit 1
    fi

    $FCXXSS_CC $OPT $LIBRARY
fi
