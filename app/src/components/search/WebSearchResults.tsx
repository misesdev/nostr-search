'use client'

import { ReactNode } from 'react';
import { User } from '@/types/types';
import { UserList } from '../user/UserList';

type Props = {
    results: User[]
}

export default function WebSearchResults({ results }: Props): ReactNode {
    return (
        <div className='w-full'>
            <UserList users={results} />
            <div className='w-full h-10'></div>
        </div>
    );
}
