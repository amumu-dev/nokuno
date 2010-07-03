import memcache
mc = memcache.Client(['localhost:11211'])
mc.flush_all()
mc.set('key', 'value')
print mc.get('key')

