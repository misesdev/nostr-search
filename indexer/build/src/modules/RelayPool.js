"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.RelayPool = void 0;
const ws_1 = require("ws");
const utils_1 = require("../utils");
class RelayPool {
    //private pubkey: string;
    constructor(relays, author) {
        this.resultEvents = [];
        this.websockets = [];
        this.pubkeys = [];
        this.subscription = "3da979448d9ba263864c4d6f14984c42";
        if (relays.length < 1)
            throw Error("expected relays");
        this.relays = relays;
        //this.pubkey = author;
        this.pubkeys = [author];
    }
    connectRelay(relay) {
        return __awaiter(this, void 0, void 0, function* () {
            return new Promise((resolve, reject) => {
                let websock = new ws_1.WebSocket(relay);
                websock.on("open", () => resolve(websock));
                websock.on("message", (message) => {
                    let data = JSON.parse(message.toString());
                    if (data[0] == "EVENT") {
                        let event = data[2];
                        let npubs = (0, utils_1.getPubkeys)(event)
                            .filter((pub) => !this.pubkeys.includes(pub));
                        npubs.forEach(pub => this.pubkeys.push(pub));
                        console.log("found users", event.tags.length);
                        if (this.resultEvents.filter(e => e.id == event.id).length <= 0) {
                            this.resultEvents.push(event);
                        }
                    }
                });
                websock.on("close", () => reject(`not connetd: ${relay}`));
                websock.on("error", () => reject(`not connetd: ${relay}`));
            });
        });
    }
    connect() {
        return __awaiter(this, void 0, void 0, function* () {
            for (let i = 0; i < this.relays.length; i++) {
                let socket = yield this.connectRelay(this.relays[i])
                    .catch(error => console.log(error));
                if (socket) {
                    this.websockets.push(socket);
                }
            }
        });
    }
    fetchEventRelay(socket, filter) {
        return __awaiter(this, void 0, void 0, function* () {
            return new Promise((resolve) => {
                socket.send(`[
                "REQ", 
                "${this.subscription}", 
                ${JSON.stringify(filter)}
            ]`);
                setTimeout(() => resolve(true), 500);
            });
        });
    }
    fechEvent(filter) {
        return __awaiter(this, void 0, void 0, function* () {
            for (let i = 0; i < this.websockets.length; i++) {
                yield this.fetchEventRelay(this.websockets[i], filter);
            }
            return this.resultEvents;
        });
    }
    fetchUser(pubkey) {
        return __awaiter(this, void 0, void 0, function* () {
            let events = yield this.fechEvent({
                kinds: [0],
                authors: [pubkey],
                limit: 1
            });
            if (events.length <= 0)
                return null;
            return events[0];
        });
    }
}
exports.RelayPool = RelayPool;
