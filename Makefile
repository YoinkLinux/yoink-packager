# PREFIX is environment variable, but if it is not set, then set default value
all:
	@echo "Installing Yoink-0.1"
install: all
	# Create directories
	install -dv ${DESTDIR}/var/cache/yoink
	install -dv ${DESTDIR}/etc/yoink/db
	install -dv ${DESTDIR}/usr/bin
	# Install files
	install -vm 755 yoink $(DESTDIR)/usr/bin
	install -vm 755 yoink-pkgr $(DESTDIR)/etc/yoink
	install -vm 644 db/yoink.db $(DESTDIR)/etc/yoink/db
	install -vm 644 mirror $(DESTDIR)/etc/yoink/
