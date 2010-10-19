mod_test.la: mod_test.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_test.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_test.la
