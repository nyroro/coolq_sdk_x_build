# -*- coding:utf-8 -*-

import json
import cqplus.six as six

if six.PY2:
    import sys
    six.moves.reload_module(sys)
    sys.setdefaultencoding('utf-8')


class CQPlusGlobalHandler(object):
    def __init__(self):
        self.app_table = dict()

    def _handle_event(self, event, params, *a, **kw):
        try:
            params = json.loads(params)
            ret_t = self.handle_event(event, params)
            ret = json.dumps({
                'code': 0,
                'data': ret_t,
            })
        except Exception as e:
            try:
                import traceback
                err = traceback.format_exc()
                if six.PY2:
                    err = err.decode('gb2312').encode('utf-8')
                ret = json.dumps({
                    'code': 1,
                    'data': err,
                })
            except:
                raise e
            
        return ret

    def handle_event(self, event, params):
        from cqplus._app import CQPlusApp

        assert isinstance(event, six.text_type)
        assert isinstance(params, dict)
        env = params['env']
        assert isinstance(env, dict)

        cq_home = env['CQ_HOME']
        app_id = env['CQ_APP_ID']

        assert isinstance(cq_home, six.text_type)
        assert isinstance(app_id, six.text_type)

        if app_id not in self.app_table:
            self.app_table[app_id] = CQPlusApp(env)
        app = self.app_table[app_id]  # type: CQPlusApp
        
        ret = bool(app.handle_event(event, params))

        if event == 'on_disable':
            del self.app_table[app_id]

        return ret
