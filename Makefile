# PREFIX is environment variable, but if it is not set, then set default value
all:
	@echo "Installing Yoink-0.1"
install: all
	install -dv ${DESTDIR}/var/cache/yoink
	install -dv ${DESTDIR}/usr/bin
	install -vm 755 yoink $(DESTDIR)/usr/bin
